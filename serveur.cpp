#include "Serveur.h"

#include <ReplicationManager.h>
#include <ClassRegistry.h>
#include <USocket.h>
#include <ConnectionTCP.h>

#include <Player.h>
#include <Enemy.h>

#include <iostream>

Serveur::Serveur(char* port)
    : rm("127.0.0.1", port, uqac::replication::ReplicationManager::Mode::SERVER)
{
    uqac::replication::ClassRegistry::Register<uqac::replication::Player>([](){ return new uqac::replication::Player(); });
    uqac::replication::ClassRegistry::Register<uqac::replication::Enemy>([](){ return new uqac::replication::Enemy(); });
}

Serveur::~Serveur()
{
    //dtor
}	

bool Serveur::Update()
{
    std::string dummy;
    dummy = "";
    std::cin >> dummy;
    if(dummy == "exit")
        return false;

    rm.Update();
    Sleep(10);
    return true;
}