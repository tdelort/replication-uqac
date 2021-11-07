#include "Client.h"

#include <ReplicationManager.h>
#include <ClassRegistry.h>
#include <USocket.h>
#include <ConnectionTCP.h>

#include <Player.h>
#include <Enemy.h>

#include <iostream>

Client::Client(char* addr, char* port)
    : rm(addr, port, uqac::replication::ReplicationManager::Mode::CLIENT)
{
    uqac::replication::ClassRegistry::Register<uqac::replication::Player>([](){ return new uqac::replication::Player(); });
    uqac::replication::ClassRegistry::Register<uqac::replication::Enemy>([](){ return new uqac::replication::Enemy(); });
}

Client::~Client()
{
    //dtor
}	

bool Client::Update()
{
    std::string dummy;
    dummy = "";
    std::cin >> dummy;
    if(dummy == "exit")
        return false;

    rm.Update();

    return true;
}