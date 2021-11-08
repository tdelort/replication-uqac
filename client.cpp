#include "Client.h"

#include <ReplicationManager.h>
#include <ClassRegistry.h>
#include <USocket.h>
#include <ConnectionTCP.h>

#include "Player.h"
#include "Enemy.h"

#include <iostream>

Client::Client(char* addr, char* port)
{
    uqac::replication::ClassRegistry::Register<uqac::replication::Player>([](){ return new uqac::replication::Player(); });
    uqac::replication::ClassRegistry::Register<uqac::replication::Enemy>([](){ return new uqac::replication::Enemy(); });

    uqac::network::Connection::Config config = {
        // On Message
        [this](uqac::network::Connection* c, uqac::span<char> msg, std::vector<uqac::network::Connection*> connections) 
        {
            rm.OnBuffer(msg);
            std::cout << std::endl << std::endl;
        },
        // On Disconnect
        [](uqac::network::Connection* c)
        {
            return;
        },
        // On Error
        [](uqac::network::Connection* c, int err)
        {
            return;
        }
    };
    uqac::network::Connection* c = sock.Connect(addr, port, uqac::network::Connection::Type::TCP);
    c->AddConfig(config);

    std::cout << "To close the client, type exit" << std::endl;
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

    return true;
}