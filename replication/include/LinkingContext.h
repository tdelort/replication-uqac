#pragma once

#include "NetworkObject.h"
#include <map>

namespace uqac::replication 
{
	class LinkingContext
	{
	public:
		using NetworkId = uint32_t;
		LinkingContext();
		~LinkingContext();

		void AddLink(NetworkObject* obj, NetworkId id);
		void DeleteObj(NetworkObject* obj);
		void AddObj(NetworkObject* obj);

		NetworkId LinkedId(NetworkObject* obj);
		NetworkObject* LinkedObj(NetworkId id);
	private:
		std::map<NetworkId, NetworkObject*> m_idToObj;
		std::map<NetworkObject*, NetworkId> m_objToId;
		int m_id;
	};
}