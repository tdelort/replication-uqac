#pragma once

namespace uqac::replication
{
    class NetworkObject
    {
    public:
        virtual void Write(uqac::serialisation::Serializer s) = 0;
        virtual void Read(uqac::serialisation::Deserializer s) = 0;
        virtual void Destroy() = 0;
    };
}