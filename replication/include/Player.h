#pragma once

#include "NetworkObject.h"

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
    class Player : public NetworkObject
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

}