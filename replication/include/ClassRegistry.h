#pragma once

#include "NetworkObject.h"

#include <functional>
#include <map>

namespace uqac::replication
{
    class ClassRegistry
    {
    private:
        ClassRegistry() = default;
        std::map<uint32_t, std::function<NetworkObject*(void)>> reg;

    public:
        ClassRegistry(const ClassRegistry&) = delete;
        ClassRegistry& operator=(const ClassRegistry&) = delete;
        ClassRegistry(ClassRegistry &&) = delete;
        ClassRegistry& operator=(const ClassRegistry&&) = delete;

        static ClassRegistry& instance()
        {
            static ClassRegistry classRegistry;
            return classRegistry;
        }

        template<typename T>
        static void Register(std::function<NetworkObject*(void)> entry);

        template<typename T>
        static T *Create();

        static NetworkObject* Create(uint32_t classId)
        {
            return instance().reg[classId]();
        }
    };

    template<typename T>
    void ClassRegistry::Register(std::function<NetworkObject*(void)> entry)
    {
        instance().reg[T::ClassID] = entry;
    }

    template<typename T>
    T *ClassRegistry::Create()
    {
        return (T*)instance().reg[T::ClassID]();
    }
}
