#include <LinkingContext.h>
#include <ClassRegistry.h>
#include <ReplicationManager.h>

#include "Player.h"
#include "Enemy.h"

#include <iostream>

int main()
{
    std::cout << "Lancement" << std::endl;

    uqac::game::Enemy e;
    e.m_vie = 500;
    e.m_position = { -100, 50, 10 };
    e.m_rotation = { 0.4964001f, 0.7791921f, 0.3227519f, -0.2056157f };
    e.m_type = uqac::game::Enemy::Boss;
    uqac::serialisation::Serializer s;
    e.Write(&s);
    uqac::serialisation::Deserializer ds (s.GetBuffer(), s.GetBufferSize());
    uqac::game::Enemy e2;
    e2.Read(&ds);

    std::cout << "vie : " << e2.m_vie << std::endl;
    std::cout << "type : " << e2.m_type << std::endl;
    std::cout << "pos : " << e2.m_position.x << " " << e2.m_position.y << " " << e2.m_position.z << std::endl;
    std::cout << "rot : " << e2.m_rotation.x << " " << e2.m_rotation.y << " " << e2.m_rotation.z << " " << e2.m_rotation.w << std::endl;

    return 0;
}