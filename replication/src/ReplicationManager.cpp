#include "ReplicationManager.h"
#include "Protocol.h"
#include <Serializer.h>

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
            // On délègue la sérialisation aux classes
            (*itr)->Write(&ser);
        }

        char* buffer = ser.GetBuffer();
        unsigned int size = ser.GetBufferSize();
        // Envoi du stream du serializer sur le réseau
    }

    void ReplicationManager::Receive()
    {
        // Récupérer le paquet jsp comment
        char* buffer = "aaabbbccc"; // = qqchose
        unsigned int size = 20; // = qqchose d'autre
        uqac::serialisation::Deserializer deser(buffer, size);

        uint32_t idProto = deser.Deserialize<uint32_t>();
        if (idProto != 0xABABBACA)
        {
            return;
        }

        uint8_t idPack = deser.Deserialize<uint8_t>();
        
        uint8_t type = deser.Deserialize<uint8_t>();
        switch (type){
            case PacketType::Hello:
                // Créer
                break;
            case PacketType::Sync:
                
                break;
            case PacketType::Bye:
                // Détruire
                break;
        }

    }
}

/*
A celui qui récupèrera les paquets :
récupération du paquet grâce à l'ID protocole
utilité numéro paquet = ?
pour tout ce qui est dans le paquet :
    on récupère la classe de l'objet (utilité ?)
    on récupère l'ID de l'objet
    on va cherche l'objet par ID dans le Linking context
    si l'objet n'existe pas :
        on le crée avec les valeurs du paquet
    sinon :
        on récupère les valeurs du paquet
        on change les valeurs de l'objet qui doivent être changées
voilà les objets sont à jour !
*/