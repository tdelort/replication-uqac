#include "ReplicationManager.h"
#include "Protocol.h"
#include "ClassRegistry.h"

#include <Serializer.h>
#include <Connection.h>
#include <ConnectionTCP.h>
#include <span.h>

#include <iostream>
#include <optional>
#include <functional>

namespace uqac::replication
{
    // Constructor
    ReplicationManager::ReplicationManager()
    { }

    ReplicationManager::~ReplicationManager()
    { 
        // TODO delete everything in the set m_obj
        for(auto it = m_obj.begin(); it != m_obj.end(); ++it)
        {
            uqac::replication::NetworkObject* obj = *it;
            if(obj)
                delete obj;
        }
    }

    NetworkObject* ReplicationManager::Create(uint32_t classId)
    {
		// Create the object using ClassRegistry
		NetworkObject* obj = ClassRegistry::Create(classId);
		// Add it to the set of objects
		m_obj.insert(obj);
		// Add it to the context
		m_context.AddObj((NetworkObject*)obj);
		return obj;
    }

    void ReplicationManager::Update(std::vector<uqac::network::Connection*>& connections)
    {
        uqac::serialisation::Serializer ser;

        ser.Serialize<uint32_t>(Protocol::ID);

        ser.Serialize<uint8_t>(static_cast<uint8_t>(Protocol::PacketType::Sync));

        uint8_t nbObj = m_obj.size();
        ser.Serialize<uint16_t>(nbObj);

        for (auto itr = m_obj.begin(); itr != m_obj.end(); itr++)
        {
            auto option = m_context.LinkedId(*itr);
            if (!option.has_value()) {
                std::cerr << "Error : No id found with object in LinkingContext" << std::endl; // print l'id ?
                exit(1);
            }
            ser.Serialize(static_cast<uint32_t>(option.value()));
            ser.Serialize(static_cast<uint32_t>((*itr)->ClassId()));
            (*itr)->Write(&ser);
        }

        // Envoi du buffer du serializer sur le réseau
        char* buffer = ser.GetBuffer();
        unsigned int size = ser.GetBufferSize();

        span<char> data(buffer, size);

        for(auto* connection : connections)
        {
            connection->Send(data);
        }
    }

    void ReplicationManager::OnBuffer(const span<char> msg)
    {
        uqac::serialisation::Deserializer ds(msg.begin(), msg.size());

        uint32_t idProto = ds.Deserialize<uint32_t>();
        if (idProto != Protocol::ID)
        {
            std::cerr << "Invalid protocol ID" << std::endl;
            return;
        }

        uint8_t type = ds.Deserialize<uint8_t>();

        switch (static_cast<Protocol::PacketType>(type))
        {
            case Protocol::PacketType::Hello:
                std::cerr << "Hello packet not supported" << std::endl;
                break;
            case Protocol::PacketType::Sync:
            {
                uint8_t n = ds.Deserialize<uint16_t>();
                for(int i = 0; i < n; i++)
                {

                    uint32_t idObj = ds.Deserialize<uint32_t>();
                    uint32_t idClass = ds.Deserialize<uint32_t>();

                    auto optObj = m_context.LinkedObj(idObj);

                    NetworkObject* obj = (optObj.has_value() ? optObj.value() : Create(idClass));

                    m_context.AddLink(obj, idObj);

                    obj->Read(&ds);
                }
                break;
            }
            case Protocol::PacketType::Bye:
                std::cerr << "Bye packet not supported" << std::endl;
                break;
            default:
                std::cerr << "Invalid packet type : " << type << std::endl;
                break;
        }
    }

    std::unordered_set<NetworkObject*>& ReplicationManager::GetObjects()
    {
        return m_obj;
    }
}