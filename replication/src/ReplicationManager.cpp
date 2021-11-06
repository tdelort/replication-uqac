#include "ReplicationManager.h"
#include "Protocol.h"
#include <Serializer.h>
#include <iostream>
#include <optional>

namespace uqac::replication
{
    ReplicationManager::ReplicationManager()
    {

    }

    ReplicationManager::~ReplicationManager()
    {

    }

    void ReplicationManager::Update()
    {
        uqac::serialisation::Serializer ser(256);

        uint32_t idProto = 0xABABBACA;
        ser.Serialize(idProto);

        uint8_t idPack = 0x02; // Aucune idée ?
        ser.Serialize(idPack);

        ser.Serialize(static_cast<uint8_t>(PacketType::Sync));

        for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++)
        {
            auto option = m_context.LinkedId(*itr);
            if (option.has_value()) {
                std::cerr << "Error : No id found with object in LinkingContext" << std::endl; // print l'id ?
                exit(1);
            }
            ser.Serialize(static_cast<uint32_t>(option.value()));
            ser.Serialize(static_cast<uint32_t>((*itr)->ClassId()));
            (*itr)->Write(&ser);
        }

        char* buffer = ser.GetBuffer();
        unsigned int size = ser.GetBufferSize();
        // Envoi du stream du serializer sur le réseau
    }

    void ReplicationManager::Receive()
    {
        // Même si on vient à bouger tout ça, ça pourra toujorus être utile
        char* buffer = "aaabbbccc"; // = qqchose
        unsigned int size = 20; // = qqchose d'autre
        uqac::serialisation::Deserializer deser(buffer, size);

        uint32_t idProto = deser.Deserialize<uint32_t>();
        if (idProto != 0xABABBACA)
        {
            // Le paquet ne nous concerne pas, donc on return
            return;
        }

        uint8_t idPack = deser.Deserialize<uint8_t>();
        
        uint8_t type = deser.Deserialize<uint8_t>();

        switch (type)
        {
            case PacketType::Hello:
                // Créer
                break;
            case PacketType::Sync:
                //sync(deser);
                break;
            case PacketType::Bye:
                // Détruire
                break;
        }
    }

}