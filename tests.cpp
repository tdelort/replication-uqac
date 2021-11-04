#include <LinkingContext.h>
#include <ClassRegistry.h>
#include <ReplicationManager.h>

#include "Player.h"

#include <iostream>

int main()
{
    /*
        //coté server
        Rm rm;
        Classreg::Regsiter<Player>(callback)
        rm.Create<Player>(/metadata/)
        // dans ↑
        Player* p = Classreg::Create<Player>(...)
        linkingContext.addlink(player)
        set.insert(player)
    */
    uqac::replication::ReplicationManager replicationManager;
    uqac::replication::ClassRegistry::Register<uqac::game::Player>([]() -> uqac::replication::NetworkObject* { return new uqac::game::Player(); });

    // After receiving a packet, the ReplicationManager will call the callback
    // function of the class that is registered to the packet type.
    // The callback function will be called with the packet as a parameter.
    // The callback function should return a pointer to the object that
    // should be replicated.
    // If the callback function returns nullptr, the packet will not be
    // replicated.
    // The ReplicationManager will then call the Replicate function of the
    // object to replicate the packet.
    // The Replicate function should return a pointer to the object that
    // should be replicated.

    //inside the On Message callback function of the USocket server
    // On Hello :
    uqac::game::Player* p = replicationManager.Create<uqac::game::Player>(/*metadata*/);
    p->Read();

    return 0;
}