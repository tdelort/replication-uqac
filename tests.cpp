#include <LinkingContext.h>
#include <ClassRegistry.h>
#include <ReplicationManager.h>

#include <Player.h>
#include <Enemy.h>

#include <iostream>

int main()
{
    std::cout << "Lancement" << std::endl;

    uqac::replication::Enemy e;
    e.m_vie = 500;
    e.m_position = { -100, 50, 10 };
    e.m_rotation = { 0.4964001f, 0.7791921f, 0.3227519f, -0.2056157f };
    e.m_type = uqac::replication::Enemy::Boss;
    uqac::serialisation::Serializer s;
    s.Serialize<uint32_t>((uint32_t)1);
    std::cout << "size : " << s.GetBufferSize() << std::endl;
    s.Serialize<uint8_t>((uint8_t)1);
    std::cout << "size : " << s.GetBufferSize() << std::endl;
    s.Serialize<uint8_t>((uint8_t)1);
    std::cout << "size : " << s.GetBufferSize() << std::endl;
    std::cout << "buffer : ";
    char* buffer = s.GetBuffer();
    for(int i = 0; i < s.GetBufferSize(); i++)
    {
        char c = (int)buffer[i];
        std::cout << (c ? c : '.');
    }
    std::cout << std::endl;


    e.Write(&s);
    uqac::serialisation::Deserializer ds(s.GetBuffer(), s.GetBufferSize());
    uqac::replication::Enemy e2;
    uint32_t i = ds.Deserialize<uint32_t>();
    uint8_t i2 = ds.Deserialize<uint8_t>();
    uint8_t i3 = ds.Deserialize<uint8_t>();
    e2.Read(&ds);

    std::cout << "test : " << (int)i2 << std::endl;
    std::cout << "test : " << (int)i << std::endl;
    std::cout << "test : " << (int)i3 << std::endl;
    std::cout << "vie : " << e2.m_vie << std::endl;
    std::cout << "type : " << e2.m_type << std::endl;
    std::cout << "pos : " << e2.m_position.x << " " << e2.m_position.y << " " << e2.m_position.z << std::endl;
    std::cout << "rot : " << e2.m_rotation.x << " " << e2.m_rotation.y << " " << e2.m_rotation.z << " " << e2.m_rotation.w << std::endl;

    std::cout << sizeof(uint8_t) << std::endl;
    std::cout << sizeof(uint16_t) << std::endl;
    std::cout << sizeof(uint32_t) << std::endl;
    std::cout << sizeof(uint64_t) << std::endl;

    return 0;
}