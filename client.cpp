#include <ReplicationManager.h>
#include <ClassRegistry.h>
#include <USocket.h>
#include <ConnectionTCP.h>

#include <Player.h>
#include <Enemy.h>

#include <iostream>

#define ADDR "127.0.0.1"
#define PORT "42069"

int main() 
{
    //uqac::replication::ClassRegistry::Register<uqac::replication::Player>([](){ return new uqac::replication::Player(); });
    //uqac::replication::ClassRegistry::Register<uqac::replication::Enemy>([](){ return new uqac::replication::Enemy(); });
	uqac::replication::ReplicationManager rm(ADDR, PORT, uqac::replication::ReplicationManager::Mode::CLIENT);

    std::string dummy;
	while (true)
	{
        dummy = "";
        std::cin >> dummy;
        if(dummy == "exit")
            break;

		rm.Update();
	}

	return 0;
}