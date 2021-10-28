#pragma once

#include <NetworkObject.h>

namespace uqac::game
{
    class Player : public NetworkObject
    {
    public:
        Vector3D m_position; // X Y entre -500 et 500 et Z entre 0 et 100
        Quaternion m_rotation;
        Vector3D m_taille; 
        int m_vie; // vie entre 0 et 300
        int m_armure; // armure entre 0 et 50
        float m_argent; // argent entre -99 999,99 et 99 999,99
        std::string m_nom; // nom de max 128 char
    };
}