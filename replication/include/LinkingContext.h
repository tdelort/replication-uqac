#pragma once

namespace uqac::replication 
{
	class NetworkObject;

	class LinkingContext
	{
	private:
		using NetworkId = uint32_t;
		std::map<NetworkId, NetworkObject*> m_idToObj;
		std::map<NetworkObject*, NetworkId> m_objToId;
	public:
		LinkingContext(std::map<NetworkId, NetworkObject*> idToObj, std::map<NetworkObject*, NetworkId> objToId);
		~LinkingContext();

		AddLink(NetworkObject* obj, NetworkId id);
		DeleteObj(NetworkObject* obj);
		AddObj(NetworkObject* obj);

		LinkedId(NetworkObject* obj);
		LinkedObj(NetworkId id);
	};
}