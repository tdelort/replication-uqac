#pragma once

#include <NetworkObject.h>

namespace uqac::game
{
    class Enemy : public NetworkObject
    {
    public:
        Vector3D m_position; // X Y entre -500 et 500 et Z entre 0 et 100
        Quaternion m_rotation;
        int m_vie; // vie entre 0 et 1000
        enum class Type {Boss, Sbire};
        Type m_type;
    };
}