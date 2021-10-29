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
		T Create();

		void Update();
	};
}