#include "ReplicationManager.h"
#include "Protocol.h"
#include "ClassRegistry.h"

#include "Player.h"
#include "Enemy.h"

#include <Serializer.h>
#include <Connection.h>
#include <ConnectionTCP.h>
#include <span.h>

#include <iostream>
#include <optional>
#include <functional>

namespace uqac::replication
{
    // Configurations

    // Called when in client mode
    void ReplicationManager::OnMessage(uqac::network::Connection* c, uqac::span<char> msg, std::vector<uqac::network::Connection*> connections)
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
                uint8_t nbObj = ds.Deserialize<uint8_t>();
                for(int i = 0; i < nbObj; i++)
                {

                    uint32_t idObj = ds.Deserialize<uint32_t>();
                    uint32_t idClass = ds.Deserialize<uint32_t>();

                    auto optObj = m_context.LinkedObj(idObj);

                    NetworkObject* obj;
                    // Couldn't get rid of this switch statement
                    switch (idClass)
                    {
                    case 'PLAY': obj = (optObj.has_value() ? optObj.value() : Create<Player>());
                        break;
                    case 'ENEM': obj = (optObj.has_value() ? optObj.value() : Create<Enemy>());
                        break;
                    }

                    m_context.AddLink(obj, idObj);

                    obj->Read(&ds);
                }
                break;
            }
            case Protocol::PacketType::Bye:
                std::cerr << "Bye packet not supported" << std::endl;
                break;
        }
    }

    void ReplicationManager::OnDisconnect(uqac::network::Connection* c)
    {
        std::cout << "disconnected" << std::endl;
    }

    void ReplicationManager::OnError(uqac::network::Connection* c, int err)
    {
        std::cout << "error : " << err << std::endl;
    }

    void ReplicationManager::OnConnect(uqac::network::Connection* c)
    {
        int nb = m_obj.size();
        if(nb == 0)
        {
            Create<Player>();
        }
        else if(nb == 1)
        {
            Create<Player>();
            Create<Enemy>();
        }
        else
        {
            return;
        }
        std::cout << "nbClients : " << nb << std::endl;
    }
    
    // Constructor
    ReplicationManager::ReplicationManager(char* addr, char* port, ReplicationManager::Mode mode)
        : m_mode(mode)
    { 
        switch (m_mode)
        {
        case Mode::CLIENT:
        {
            uqac::network::Connection* c = m_sock.Connect(addr, port, uqac::network::Connection::Type::TCP);
            c->AddConfig({
                [this](uqac::network::Connection* c, uqac::span<char> msg, std::vector<uqac::network::Connection*> connections) {OnMessage(c,msg,connections);},
                [this](uqac::network::Connection* c) {OnDisconnect(c);},
                [this](uqac::network::Connection* c, int err) {OnError(c, err);}
            });
            break;
        }
        case Mode::SERVER:
            m_sock.Listen(port, {[this](uqac::network::Connection* c) {OnConnect(c);}});
        }
    }

    ReplicationManager::~ReplicationManager()
    { 
        // TODO delete everything in the set m_obj
    }

    void ReplicationManager::Update()
    {
        switch (m_mode)
        {
        case Mode::CLIENT:
            ClientUpdate();
            break;
        case Mode::SERVER:
            ServerUpdate();
            break;
        }
    }

    void ReplicationManager::ClientUpdate()
    {
        std::cout << "ClientUpdate" << std::endl;
    }

    void ReplicationManager::ServerUpdate()
    {
        uqac::serialisation::Serializer ser(ReplicationManager::SERIALIZATION_BUFFER_SIZE);

        ser.Serialize(Protocol::ID);

        ser.Serialize(static_cast<uint8_t>(Protocol::PacketType::Sync));

        ser.Serialize(static_cast<uint8_t>(m_obj.size()));

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
        std::vector<uqac::network::Connection*> connections = m_sock.GetAllConnections();
        for(auto* connection : connections)
        {
            connection->Send(data);
        }
    }
}