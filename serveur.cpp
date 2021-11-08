#include "Serveur.h"

#include <ReplicationManager.h>
#include <ClassRegistry.h>
#include <USocket.h>
#include <ConnectionTCP.h>

#include "Player.h"
#include "Enemy.h"

#include <iostream>

Serveur::Serveur(char* port)
{
    uqac::replication::ClassRegistry::Register<uqac::replication::Player>([](){ return new uqac::replication::Player(); });
    uqac::replication::ClassRegistry::Register<uqac::replication::Enemy>([](){ return new uqac::replication::Enemy(); });

    uqac::network::USocket::Config config = 
    {
        // On Connect
        [this](uqac::network::Connection* c)
        {
            c->AddConfig({
                [](uqac::network::Connection* c, uqac::span<char> msg, std::vector<uqac::network::Connection*> connections) {return;},
                [](uqac::network::Connection* c) {return;},
                [](uqac::network::Connection* c, int err) {return;}
            });

            std::unordered_set<uqac::replication::NetworkObject*> objects = rm.GetObjects();
            int nb = objects.size();

            if(nb == 0)
                rm.Create<uqac::replication::Player>();
            else if(nb == 1)
            {
                rm.Create<uqac::replication::Player>();
                rm.Create<uqac::replication::Enemy>();
            }
            else
                return;

        }
    };

    sock.Listen(port, config);

    std::cout << "To close the server, type exit" << std::endl;
    std::cout << "To Randomize the values in the network object, type anything else" << std::endl;
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

    std::unordered_set<uqac::replication::NetworkObject*> objects = rm.GetObjects();
    for(auto it = objects.begin(); it != objects.end(); ++it)
    {
        uqac::replication::NetworkObject* obj = *it;
        switch (obj->ClassId())
        {
            case 'PLAY':
            {
                uqac::replication::Player* player = (uqac::replication::Player*)obj;
                player->Randomize();
                break;
            }
            case 'ENEM':
            {
                uqac::replication::Enemy* enemy = (uqac::replication::Enemy*)obj;
                enemy->Randomize();
                break;
            }
        }
    }

    rm.Update(sock.GetAllConnections());
    std::cout << std::endl << std::endl;
    return true;
}