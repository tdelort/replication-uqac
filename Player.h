#pragma once

#include "framework.h"
#include <NetworkObject.h>

#include <string>
#include <iostream>

namespace uqac::game
{
    class Player : public uqac::replication::NetworkObject
    {
    public:
        enum {ClassID = 'PLAY'};

        Vector3D m_position; // X Y entre -500 et 500 et Z entre 0 et 100
        Quaternion m_rotation;
        Vector3D m_taille; 
        int m_vie; // vie entre 0 et 300
        int m_armure; // armure entre 0 et 50
        float m_argent; // argent entre -99 999,99 et 99 999,99
        std::string m_nom; // nom de max 128 char

        Player();

        void Write() override;
        void Read() override;
        void Destroy() override;
    };

    Player::Player()
        : m_position({0, 0, 0}), m_rotation({0, 0, 0, 1}), m_taille({1, 1, 1}), m_vie(100), m_armure(0), m_argent(0), m_nom("")
    { }

    void Player::Write()
    {
        //TODO
        std::cout << "Write" << std::endl;
    }

    void Player::Read()
    {
        //TODO
        std::cout << "Read" << std::endl;
    }

    void Player::Destroy()
    {
        //TODO
        std::cout << "Destroy" << std::endl;
    }
}