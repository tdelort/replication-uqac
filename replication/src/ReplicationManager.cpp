#include "ReplicationManager.h"

ReplicationManager::ReplicationManager()
{

}

ReplicationManager::~ReplicationManager()
{

}

void ReplicationManager::Update()
{
    for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++)
    {
        //on verra plus tard
    }
}

/*
pour la fct create :
T Create(...)
{
    Player* p = Classreg::Create<Player>(...)
    m_context.Create(player)
    m_set.insert(player)
    puis tout ce qui est réseau ....
}
*/