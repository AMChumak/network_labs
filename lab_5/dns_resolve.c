#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <ares.h>

typedef struct {
  ares_channel_t   *channel;
  struct pollfd    *poll_fds;
  size_t            poll_nfds;
  size_t            poll_fds_alloc;

  ares_fd_events_t *ares_fds;
  size_t            ares_nfds;
} dnsstate_t;

void sock_state_cb(void *data, ares_socket_t socket_fd, int readable, int writable)
{
  dnsstate_t *state = data;
  size_t      idx;

  /* Find match */
  for (idx=0; idx<state->poll_nfds; idx++) {
    if (state->poll_fds[idx].fd == socket_fd) {
      break;
    }
  }

  /* Not found */
  if (idx >= state->poll_nfds) {
    /* Do nothing */
    if (!readable && !writable) {
      return;
    }

    /* Add */
    state->poll_nfds++;
    if (state->poll_nfds > state->poll_fds_alloc) {
      state->poll_fds_alloc = state->poll_nfds;

      state->poll_fds = realloc(state->poll_fds,
                                sizeof(*state->poll_fds) * state->poll_nfds);

      /* Make the ares_fds the same size */
      state->ares_fds = realloc(state->ares_fds,
                                sizeof(*state->ares_fds) * state->poll_nfds);
    }
  } else {
    /* Remove */
    if (!readable && !writable) {
      memmove(&state->poll_fds[idx], &state->poll_fds[idx+1],
              sizeof(*state->poll_fds) * (state->poll_nfds - idx - 1));
      state->poll_nfds--;
      return;
    }
  }

  /* Update Poll Events (including on Add) */
  state->poll_fds[idx].fd     = socket_fd;
  state->poll_fds[idx].events = 0;
  if (readable) {
    state->poll_fds[idx].events |= POLLIN;
  }
  if (writable) {
    state->poll_fds[idx].events |= POLLOUT;
  }
}

void process(dnsstate_t *state)
{
  struct timeval tv;

  while (1) {
    int            rv;
    int            timeout;
    size_t         i;

    /* Since we don't have any other program state to wait on, we'll just
     * stop looping when we know there are no remaining queries, which is
     * easily indicated by ares_timeout() returning NULL when maxtv is NULL */
    if (ares_timeout(state->channel, NULL, &tv) == NULL) {
      break;
    }

    timeout = tv.tv_sec * 1000 + tv.tv_usec / 1000;

    rv = poll(state->poll_fds, state->poll_nfds, timeout);
    if (rv < 0) {
      continue;
    } else if (rv == 0) {
      /* Process timeouts */
      ares_process_fd(state->channel, ARES_SOCKET_BAD, ARES_SOCKET_BAD);
      continue;
    }

    /* Form our notification array */
    state->ares_nfds = 0;
    for (i=0; i<state->poll_nfds; i++) {
      size_t idx;
      if (state->poll_fds[i].revents == 0) {
        continue;
      }

      idx = state->ares_nfds++;

      state->ares_fds[idx].fd     = state->poll_fds[i].fd;
      state->ares_fds[idx].events = 0;
      if (state->poll_fds[i].revents & (POLLERR|POLLHUP|POLLIN)) {
        state->ares_fds[idx].events |= ARES_FD_EVENT_READ;
      }
      if (state->poll_fds[i].revents & POLLOUT) {
        state->ares_fds[idx].events |= ARES_FD_EVENT_WRITE;
      }
    }

    /* Notify about read/write events per FD */
    ares_process_fds(state->channel, state->ares_fds, state->ares_nfds,
                     ARES_PROCESS_FLAG_NONE);
  }
}

/* Callback that is called when DNS query is finished */
static void addrinfo_cb(void *arg, int status, int timeouts,
                        struct ares_addrinfo *result)
{
  (void)arg; /* Example does not use user context */
  printf("Result: %s, timeouts: %d\n", ares_strerror(status), timeouts);

  if (result) {
    struct ares_addrinfo_node *node;
    for (node = result->nodes; node != NULL; node = node->ai_next) {
      char        addr_buf[64] = "";
      const void *ptr          = NULL;
      if (node->ai_family == AF_INET) {
        const struct sockaddr_in *in_addr =
          (const struct sockaddr_in *)((void *)node->ai_addr);
        ptr = &in_addr->sin_addr;
      } else if (node->ai_family == AF_INET6) {
        const struct sockaddr_in6 *in_addr =
          (const struct sockaddr_in6 *)((void *)node->ai_addr);
        ptr = &in_addr->sin6_addr;
      } else {
        continue;
      }
      ares_inet_ntop(node->ai_family, ptr, addr_buf, sizeof(addr_buf));
      printf("Addr: %s\n", addr_buf);
    }
  }
  ares_freeaddrinfo(result);
}

int main(int argc, char **argv)
{
  dnsstate_t                 state;
  struct ares_options        options;
  int                        optmask = 0;
  struct ares_addrinfo_hints hints;

  memset(&state, 0, sizeof(state));

  if (argc != 2) {
    printf("Usage: %s domain\n", argv[0]);
    return 1;
  }

  /* Initialize library */
  ares_library_init(ARES_LIB_INIT_ALL);

  /* Enable sock state callbacks, we should not use ares_fds() or ares_getsock()
   * in modern implementations. */
  memset(&options, 0, sizeof(options));
  optmask                   |= ARES_OPT_SOCK_STATE_CB;
  options.sock_state_cb      = sock_state_cb;
  options.sock_state_cb_data = &state;

  /* Initialize channel to run queries, a single channel can accept unlimited
   * queries */
  if (ares_init_options(&state.channel, &options, optmask) != ARES_SUCCESS) {
    printf("c-ares initialization issue\n");
    return 1;
  }

  /* Perform an IPv4 and IPv6 request for the provided domain name */
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_flags  = ARES_AI_CANONNAME;
  ares_getaddrinfo(state.channel, argv[1], NULL, &hints, addrinfo_cb,
                   NULL /* user context not specified */);

  /* Wait until no more requests are left to be processed */
  process(&state);

  /* Cleanup */
  ares_destroy(state.channel);
  free(state.poll_fds);
  free(state.ares_fds);

  ares_library_cleanup();
  return 0;
}