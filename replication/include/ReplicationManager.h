#pragma once

#include "LinkingContext.h"
#include "NetworkObject.h"
#include <unordered_set>

namespace uqac::replication
{
	class ReplicationManager
	{
	private:
		std::unordered_set<NetworkObject*> m_obj;
		LinkingContext m_context;
	public:
		ReplicationManager();
		~ReplicationManager();

		template<typename T>
		T* Create();

		void Update();
		void Receive();
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

		//La partie reseau
		//TODO ?

		return obj;
	}
}