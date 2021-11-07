#pragma once

#include <Serializer.h>
#include <Deserializer.h>

namespace uqac::replication
{
    class NetworkObject
    {
    public:
        virtual uint32_t ClassId() = 0;
        virtual void Write(uqac::serialisation::Serializer* s) = 0;
        virtual void Read(uqac::serialisation::Deserializer* s) = 0;
        virtual void Destroy() = 0;
    };
}