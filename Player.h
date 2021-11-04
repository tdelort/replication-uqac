#pragma once

#include <NetworkObject.h>

#include <IntCompressor.h>
#include <FloatCompressor.h>
#include <QuatCompressor.h>
#include <VectCompressor.h>

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

        uint32_t ClassId() override;
        void Write(uqac::serialisation::Serializer* s) override;
        void Read(uqac::serialisation::Deserializer* s) override;
        void Destroy() override;
    };

    Player::Player()
        : m_position({0, 0, 0}), m_rotation({0, 0, 0, 1}), m_taille({1, 1, 1}), m_vie(100), m_armure(0), m_argent(0), m_nom("")
    { }

    uint32_t Player::ClassId() {
        return ClassID;
    }

    void Player::Write(uqac::serialisation::Serializer* s)
    {
        uqac::serialisation::IntCompressor vieComp(0, 300);
        uqac::serialisation::IntCompressor armureComp(0, 50);
        uqac::serialisation::FloatCompressor argentComp(- 99999.99, 99999.99, 3);
        uqac::serialisation::VectCompressor positionComp({ -500, -500, 0 }, { 500, 500, 100 }, { 3, 3, 3 });
        uqac::serialisation::VectCompressor tailleComp({ 0, 0, 0 }, { 10, 10, 20 }, { 3, 3, 3 });
        uqac::serialisation::QuatCompressor rotationComp;

        vieComp.Compress(s, m_vie);
        armureComp.Compress(s, m_armure);
        argentComp.Compress(s, m_argent);
        positionComp.Compress(s, m_position);
        tailleComp.Compress(s, m_taille);
        rotationComp.Compress(s, m_rotation);

        std::cout << "Write" << std::endl;
    }

    void Player::Read(uqac::serialisation::Deserializer* s)
    {
        uqac::serialisation::IntCompressor vieComp(0, 300);
        uqac::serialisation::IntCompressor armorComp(0, 50);
        uqac::serialisation::FloatCompressor moneyComp(-99999.99, 99999.99, 3);
        uqac::serialisation::VectCompressor positionComp({ -500, -500, 0 }, { 500, 500, 100 }, { 3, 3, 3 });
        uqac::serialisation::VectCompressor tailleComp({ 0, 0, 0 }, { 10, 10, 20 }, { 3, 3, 3 });
        uqac::serialisation::QuatCompressor rotationComp;

        m_vie = vieComp.Decompress(s);
        m_armure = armorComp.Decompress(s);
        m_argent = moneyComp.Decompress(s);
        m_position = positionComp.Decompress(s);
        m_taille = tailleComp.Decompress(s);
        m_rotation = rotationComp.Decompress(s);

        std::cout << "Read" << std::endl;
    }

    void Player::Destroy()
    {
        //TODO
        std::cout << "Destroy" << std::endl;
    }
}