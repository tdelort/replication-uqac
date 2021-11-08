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

		ReplicationManager();
		~ReplicationManager();

		template<typename T>
		T* Create();

		NetworkObject* Create(uint32_t classId);

		void Update(std::vector<uqac::network::Connection*>& connections);

		void OnBuffer(const span<char> msg);

		std::unordered_set<NetworkObject*>& GetObjects();
	private:
		std::unordered_set<NetworkObject*> m_obj;
		LinkingContext m_context;
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
}