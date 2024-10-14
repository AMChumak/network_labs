
#include "ConnectManager.h"
#include "Worker.h"
using namespace tcpServer;



int main(int argc, char **argv){
    boost::asio::io_context serverContext;
    Worker prototype{serverContext};
    ConnectManager manager{std::stoi(argv[1]), &prototype};
    std::thread connectManagerThread{&ConnectManager::handleConnects, &manager};
    std::thread checkerThread{&ConnectManager::checkSpeed, &manager};
    char stopFlag;
    std::cin >> stopFlag;
    manager.isTerminated = 1;
    connectManagerThread.join();
    checkerThread.join();
    return 0;
}