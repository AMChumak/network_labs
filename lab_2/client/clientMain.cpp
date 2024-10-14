
#include "Client.h"
using namespace tcpClient;



int main(int argc, char **argv)
{
    //arg[1]  - path (string)
    //arg[2] - address (string, ipv4 format)
    //arg[2] - port (int)
    const std::string path{argv[1]};
    const std::string address{argv[2]};
    ConnectManager manager{address, std::stoi(argv[3])};
    FileReader reader{path};
    Client client{&manager, &reader};

    client.sendFile();

    return 0;
}