#pragma once

#include "framework.h"
#include <NetworkObject.h>

namespace uqac::game
{
    class Enemy : public uqac::replication::NetworkObject
    {
    public:
        enum {ClassID = 'ENEM'};

        Vector3D m_position; // X Y entre -500 et 500 et Z entre 0 et 100
        Quaternion m_rotation;
        int m_vie; // vie entre 0 et 1000
        enum Type {Boss, Sbire};
        Type m_type;

        Enemy();

        void Write(uqac::serialisation::Serializer* s) override;
        void Read(uqac::serialisation::Deserializer* s) override;
        void Destroy() override;
    };

    Enemy::Enemy()
        : m_position({0, 0, 0}), m_rotation({0, 0, 0, 1}), m_vie(100), m_type(Type::Sbire)
    { }

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

        Enemy e;

        e.m_vie = vieComp.Decompress(s);
        e.m_position = positionComp.Decompress(s);
        e.m_rotation = rotationComp.Decompress(s);
        e.m_type = (Type)typeComp.Decompress(s);

        std::cout << "Read" << std::endl;
    }

    void Enemy::Destroy()
    {
        //TODO
        std::cout << "Destroy" << std::endl;
    }
}