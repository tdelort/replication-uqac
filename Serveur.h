#pragma once

#include <ReplicationManager.h>

class Serveur
{
public:
    Serveur(char* port);
    ~Serveur();

    bool Update();
private:
   uqac::replication::ReplicationManager rm; 
};