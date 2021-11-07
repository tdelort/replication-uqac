#include "LinkingContext.h"
#include "NetworkObject.h"

#include <optional>

namespace uqac::replication
{
	LinkingContext::LinkingContext()
	{
		m_idToObj = std::map<NetworkId, NetworkObject*>();
		m_objToId = std::map<NetworkObject*, NetworkId>();
		m_id = 0;
	}

	LinkingContext::~LinkingContext()
	{
		//TODO
	}

	void LinkingContext::AddLink(NetworkObject* obj, NetworkId id)
	{
		m_idToObj.insert({ id, obj });
		m_objToId.insert({ obj, id });
	}

	void LinkingContext::DeleteObj(NetworkObject* obj)
	{
		auto search = m_objToId.find(obj);
		if (search != m_objToId.end()) 
		{
			m_idToObj.erase(search->second);
			m_objToId.erase(search);
		}
	}

	void LinkingContext::AddObj(NetworkObject* obj)
	{
		AddLink(obj, m_id);
		m_id += 1;
	}

	std::optional<LinkingContext::NetworkId> LinkingContext::LinkedId(NetworkObject* obj) 
	{
		auto search = m_objToId.find(obj);
		if (search != m_objToId.end()) 
		{
			return search->second;
		}
		return {};
	}

	std::optional<NetworkObject*> LinkingContext::LinkedObj(NetworkId id)
	{
		auto search = m_idToObj.find(id);
		if (search != m_idToObj.end())
		{
			return search->second;
		}
		return {};
	}
}