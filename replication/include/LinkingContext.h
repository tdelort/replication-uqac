#pragma once

#include "NetworkObject.h"
#include <map>

namespace uqac::replication 
{
	class LinkingContext
	{
	private:
		using NetworkId = uint32_t;
		std::map<NetworkId, NetworkObject*> m_idToObj;
		std::map<NetworkObject*, NetworkId> m_objToId;
	public:
		LinkingContext(std::map<NetworkId, NetworkObject*> idToObj, std::map<NetworkObject*, NetworkId> objToId);
		~LinkingContext();

		void AddLink(NetworkObject* obj, NetworkId id);
		void DeleteObj(NetworkObject* obj);
		void AddObj(NetworkObject* obj);

		void LinkedId(NetworkObject* obj);
		void LinkedObj(NetworkId id);
	};
}