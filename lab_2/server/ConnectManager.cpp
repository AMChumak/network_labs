//
// Created by anton on 9/25/24.
//

#include "ConnectManager.h"

#include <iostream>

using namespace tcpServer;
using boost::asio::ip::tcp;

ConnectManager::ConnectManager(const int port, ServerWorkerI* workerPrototype):
    acceptor_(context_, tcp::endpoint(tcp::v4(), port)), prototype_(workerPrototype)
{
}


ConnectManager::~ConnectManager()
{
    for (const auto worker : workers_)
    {
        delete worker.first;
    }
    workers_.clear();
}

void ConnectManager::handleConnects()
{
    for (;;)
    {
        //check whole connections
        for (auto worker = workers_.begin(); worker != workers_.end(); ++worker)
        {
            if ((*worker).first->getStatus() == read)
            {
                const ServerWorkerI* delWorker = worker->first;
                worker = workers_.erase(worker);
                delete delWorker;
            }
        }

        //add new connection
        workers_.emplace_back(prototype_->clone(), 0ULL);
        acceptor_ = workers_.back().first->accept(std::move(acceptor_));
        workers_.back().first->initWork();
    }
}

void ConnectManager::checkSpeed()
{
    while (!isTerminated)
    {
        system("clear");
        for (auto worker = workers_.begin(); worker != workers_.end(); ++worker)
        {
            if ((*worker).first->getStatus() == stoppedFailed)
            {
                std::cout << "|------------------------------|";
                unsigned long long curRecvNum = worker->first->getRecievedNum();
                std::cout << worker->first->getEndpointAddressPort() << " |   Fail    |   " << static_cast<double>(
                        curRecvNum - worker->second) / (3.0 - std::chrono::duration_cast<std::chrono::microseconds>(
                        std::chrono::system_clock::now() - worker->first->getStopTime()).count() / 1000000.0) << "  |  " <<
                    static_cast<double>(curRecvNum)
                    / (std::chrono::duration_cast<std::chrono::microseconds>(
                        worker->first->getStopTime() - worker->first->getStartTime()).count() / 1000000.0) << std::endl;

                worker->first->setStatus(read);
                worker->second = curRecvNum;
            }
            else if ((*worker).first->getStatus() == stoppedSuccessful)
            {
                std::cout << "|++++++++++++++++++++++++++++++|";
                unsigned long long curRecvNum = worker->first->getRecievedNum();
                std::cout << worker->first->getEndpointAddressPort() << " |  Success  |   " << static_cast<double>(
                        curRecvNum - worker->second) / (3.0 - (std::chrono::duration_cast<std::chrono::microseconds>(
                        std::chrono::system_clock::now() - worker->first->getStopTime()).count() / 1000000.0)) << "  |  "
                    << static_cast<double>(curRecvNum) / (std::chrono::duration_cast<std::chrono::microseconds>(
                        worker->first->getStopTime() - worker->first->getStartTime()).count() / 1000000.0) << std::endl;
                worker->first->setStatus(read);
                worker->second = curRecvNum;
            }
            else if ((*worker).first->getStatus() == inWork)
            {
                unsigned long long curRecvNum = worker->first->getRecievedNum();
                std::cout << "|";
                int i = 0;
                for (; i < 15.0 * curRecvNum / worker->first->getFileLength(); i++)
                {
                    std::cout << ">>";
                }
                for (; i < 15; ++i)
                {
                    std::cout << "  ";
                }
                std::cout << "|";


                std::cout << worker->first->getEndpointAddressPort() << " |  in work  |   " << static_cast<double>(
                        curRecvNum - worker->second) / 3.0 << "  |  " << static_cast<double>(curRecvNum)
                    / (std::chrono::duration_cast<std::chrono::microseconds>(
                        std::chrono::system_clock::now() - worker->first->getStartTime()).count() / 1000000.0) <<std::endl;


                worker->second = curRecvNum;
            }
        }
        sleep(3);
    }
}
