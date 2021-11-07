#pragma once

#include "LinkingContext.h"
#include "NetworkObject.h"

#include <Connection.h>
#include <USocket.h>

#include <unordered_set>

namespace uqac::replication
{
	class ReplicationManager
	{
	public:
		static const int SERIALIZATION_BUFFER_SIZE = 256;

		enum class Mode
		{
			SERVER,
			CLIENT
		};

		ReplicationManager(char* addr, char* port, Mode mode);
		~ReplicationManager();

		template<typename T>
		T* Create();

		void Update();
	private:
		std::unordered_set<NetworkObject*> m_obj;
		LinkingContext m_context;
        uqac::network::USocket m_sock;
		Mode m_mode;

		void OnMessage(uqac::network::Connection* c, uqac::span<char> msg, std::vector<uqac::network::Connection*> connections);
        void OnDisconnect(uqac::network::Connection* c);
        void OnError(uqac::network::Connection* c, int err);
		void OnConnect(uqac::network::Connection* c);
		void ClientUpdate();
		void ServerUpdate();
	};

	template<typename T>
	T* ReplicationManager::Create()
	{
		// Create the object using ClassRegistry
		T* obj = ClassRegistry::Create<T>();
		// Add it to the set of objects
		m_obj.insert(obj);
		// Add it to the context
		m_context.AddObj((NetworkObject*)obj);
		return obj;
	}

	void sync(uqac::serialisation::Deserializer deser);
}