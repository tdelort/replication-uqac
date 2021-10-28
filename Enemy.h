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
        enum class Type {Boss, Sbire};
        Type m_type;
    };
}