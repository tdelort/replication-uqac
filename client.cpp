#include <ReplicationManager.h>
#include <USocket.h>
#include <ConnectionTCP.h>

#define ADDR "127.0.0.1"
#define PORT "42069"
int main() 
{
	uqac::network::USocket client;
	uqac::network::ConnectionTCP* c = (uqac::network::ConnectionTCP*)client.Connect(ADDR, PORT, uqac::network::Connection::Type::TCP);
	uqac::replication::ReplicationManager replicationManager;

	replicationManager.AddConnection(c);

	while (true)
	{
		replicationManager.Update();
	}

	return 0;
}