#pragma once

#include "LinkingContext.h"

namespace uqac::replication
{
	class NetworkObject;

	class ReplicationManager
	{
	private:
		std::unordered_set<NetworkObject> m_obj;
		LinkingContext m_context;
	public:
		ReplicationManager(std::unordered_set<NetworkObject> m_obj, LinkingContext context);
		~ReplicationManager();

		Update();
	};
}