#include <USocket.h>
#include <ConnectionTCP.h>

#include <iostream>
#include <string>

#define DEFAULT_PORT "1234"

// callback pour les messages recus
void OnMessage(uqac::network::Connection* c, std::string msg, std::vector<uqac::network::Connection*> connections)
{
    std::cout << "Message received: " << msg << std::endl;
}

// callback pour les deconnexions
void OnDisconnect(uqac::network::Connection* c)
{
    std::cout << "Client disconnected" << std::endl;
}

// callback pour les erreurs
void OnError(uqac::network::Connection* c, int error)
{
    std::cout << "Error: " << error << std::endl;
}

int main()
{
    uqac::network::Connection::Config config_msg = {
        OnMessage,
        OnDisconnect,
        OnError
    };

	uqac::network::USocket client;

	uqac::network::ConnectionTCP* c = (uqac::network::ConnectionTCP*)client.Connect("127.0.0.1", DEFAULT_PORT, uqac::network::Connection::Type::TCP);
	c->AddConfig(config_msg);
    
    // envoi d'un message
    c->Send(msg);
}