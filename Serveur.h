#pragma once

#include <USocket.h>
#include <ReplicationManager.h>

class Serveur
{
public:
    Serveur(char* port);
    ~Serveur();

    bool Update();
private:
   uqac::replication::ReplicationManager rm; 
   uqac::network::USocket sock;
};