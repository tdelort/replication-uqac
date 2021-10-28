#include "LinkingContext.h"
#include "NetworkObject.h"

namespace uqac::replication
{
	class LinkingContext
	{
		LinkingContext()
		{
			m_idToObj = std::map<NetworkId, NetworkObject*>();
			m_objToId = std::map<NetworkObject*, NetworkId>();
			m_id = 0;
		}

		~LinkingContext()
		{
			//TODO
		}

		void AddLink(NetworkObject* obj, NetworkId id)
		{
			m_idToObj.insert({ id, obj });
			m_objToId.insert({ obj, id });
			m_id += 1;
		}

		void DeleteObj(NetworkObject* obj)
		{
			auto search1 = m_idToObj.find(obj);
			m_idToObj.erase(search1);
			auto search2 = m_objToId.find(obj);
			m_objToId.erase(search2);
		}

		void AddObj(NetworkObject* obj)
		{
			
		}
	};
}