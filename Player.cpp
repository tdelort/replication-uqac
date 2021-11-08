#include "Player.h"

#include "NetworkObject.h"

#include "framework.h"

#include <IntCompressor.h>
#include <FloatCompressor.h>
#include <QuatCompressor.h>
#include <VectCompressor.h>

#include <Serializer.h>
#include <Deserializer.h>

#include <string>
#include <iostream>

namespace uqac::replication
{

    Player::Player()
        : m_position({-400, 0, 90}), m_rotation({0.4964001f, 0.7791921f, 0.3227519f, -0.2056157f}), m_taille({2, 3, 5}), m_vie(100), m_armure(25), m_argent(6789), m_nom("")
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

        std::cout << "Position : " << m_position.x << " " << m_position.y << " " << m_position.z << std::endl;
        std::cout << "Rotation : " << m_rotation.x << " " << m_rotation.y << " " << m_rotation.z << " " << m_rotation.w << std::endl;
        std::cout << "Taille : " << m_taille.x << " " << m_taille.y << " " << m_taille.z << std::endl;
        std::cout << "Vie : " << m_vie << std::endl;
        std::cout << "Armure : " << m_armure << std::endl;
        std::cout << "Argent : " << m_argent << std::endl;
        std::cout << "Nom : " << m_nom << std::endl;
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

        std::cout << "Read Player" << std::endl;

        std::cout << "Position : " << m_position.x << " " << m_position.y << " " << m_position.z << std::endl;
        std::cout << "Rotation : " << m_rotation.x << " " << m_rotation.y << " " << m_rotation.z << " " << m_rotation.w << std::endl;
        std::cout << "Taille : " << m_taille.x << " " << m_taille.y << " " << m_taille.z << std::endl;
        std::cout << "Vie : " << m_vie << std::endl;
        std::cout << "Armure : " << m_armure << std::endl;
        std::cout << "Argent : " << m_argent << std::endl;
        std::cout << "Nom : " << m_nom << std::endl;
    }

    void Player::Destroy()
    {
        //TODO
        std::cout << "Destroy" << std::endl;
    }

    void Player::Randomize()
    {
        m_vie = frand(0, 300);
        m_armure = frand(0, 50);
        m_argent = frand(-99999.99, 99999.99);
        m_position.x = frand(-500, 500);
        m_position.y = frand(-500, 500);
        m_position.z = frand(0, 100);
        m_taille.x = frand(0, 10);
        m_taille.y = frand(0, 10);
        m_taille.z = frand(0, 20);
        m_rotation = RandomQuaternion();
    }

}