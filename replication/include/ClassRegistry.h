#pragma once

#include <functional>
#include <map>

#include "NetworkObject.h"

namespace uqac::replication
{
    class ClassRegistry
    {
    private:
        ClassRegistry();
        std::map<uint32_t, std::function<NetworkObject(void)>> reg;

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
        static void Register<T>(std::function<NetworkObject(void)>);

        static NetworkObject Create(uint32_t classID);
    };
}