#pragma once

#include <ReplicationManager.h>

class Client
{
public:
    Client(char* addr, char* port);
    ~Client();

    bool Update();
private:
   uqac::replication::ReplicationManager rm; 
};