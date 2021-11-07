#pragma once

#include "NetworkObject.h"

#include <IntCompressor.h>
#include <FloatCompressor.h>
#include <QuatCompressor.h>
#include <VectCompressor.h>

#include <string>
#include <iostream>

namespace uqac::replication
{
    class Enemy : public NetworkObject
    {
    public:
        enum {ClassID = 'ENEM'};

        Vector3D m_position; // X Y entre -500 et 500 et Z entre 0 et 100
        Quaternion m_rotation;
        int m_vie; // vie entre 0 et 1000
        enum Type {Boss, Sbire};
        Type m_type;

        Enemy();

        uint32_t ClassId() override;
        void Write(uqac::serialisation::Serializer* s) override;
        void Read(uqac::serialisation::Deserializer* s) override;
        void Destroy() override;
    };
}