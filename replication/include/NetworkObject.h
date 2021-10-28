#pragma once

namespace uqac::replication
{
    class NetworkObject
    {
    public:
        virtual void Write() = 0;
        virtual void Read() = 0;
        virtual void Destroy() = 0;
    };
}