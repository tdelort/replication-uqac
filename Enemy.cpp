#include "Enemy.h"

#include "NetworkObject.h"

#include "framework.h"

#include <IntCompressor.h>
#include <FloatCompressor.h>
#include <QuatCompressor.h>
#include <VectCompressor.h>

#include <string>
#include <iostream>

namespace uqac::replication
{
    Enemy::Enemy()
        : m_position({0, 0, 0}), m_rotation({0, 0, 0, 1}), m_vie(100), m_type(Sbire)
    { }

    uint32_t Enemy::ClassId() {
        return ClassID;
    }

    void Enemy::Write(uqac::serialisation::Serializer* s)
    {
        uqac::serialisation::IntCompressor vieComp(0, 1000);
        uqac::serialisation::VectCompressor positionComp({ -500, -500, 0 }, { 500, 500, 100 }, { 3, 3, 3 });
        uqac::serialisation::QuatCompressor rotationComp;
        uqac::serialisation::IntCompressor typeComp(0, 1);

        vieComp.Compress(s, m_vie);
        positionComp.Compress(s, m_position);
        rotationComp.Compress(s, m_rotation);
        typeComp.Compress(s, m_type);

        std::cout << "Write" << std::endl;
    }

    void Enemy::Read(uqac::serialisation::Deserializer* s)
    {
        uqac::serialisation::IntCompressor vieComp(0, 1000);
        uqac::serialisation::VectCompressor positionComp({ -500, -500, 0 }, { 500, 500, 100 }, { 3, 3, 3 });
        uqac::serialisation::QuatCompressor rotationComp;
        uqac::serialisation::IntCompressor typeComp(0, 1);

        m_vie = vieComp.Decompress(s);
        m_position = positionComp.Decompress(s);
        m_rotation = rotationComp.Decompress(s);
        m_type = (Type)typeComp.Decompress(s);

        std::cout << "Read Enemy" << std::endl;

        std::cout << "Position : " << m_position.x << " " << m_position.y << " " << m_position.z << std::endl;
        std::cout << "Rotation : " << m_rotation.x << " " << m_rotation.y << " " << m_rotation.z << " " << m_rotation.w << std::endl;
        std::cout << "Vie : " << m_vie << std::endl;
        std::cout << "Type : " << m_type << std::endl;

    }

    void Enemy::Destroy()
    {
        //TODO
        std::cout << "Destroy" << std::endl;
    }

    void Enemy::Randomize()
    {
        m_vie = frand(0, 1000);
        m_position.x = frand(-500, 500);
        m_position.y = frand(-500, 500);
        m_position.z = frand(0, 100);
        m_rotation = RandomQuaternion();
        m_type = static_cast<Enemy::Type>(rand() % 2);
    }   
}