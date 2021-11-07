#pragma once

namespace uqac::replication
{
    namespace Protocol
    {
        enum class PacketType : uint8_t
        {
            Hello = 0x00,
            Sync = 0x01,
            Bye = 0x02,
            PacketType_Max
        };

        constexpr uint32_t ID = 0xDEADBEEF;

        //FYI: This is what a packet looks like
        // struct PacketHeader
        // {
        //     uint32_t id;
        //     PacketType type;
        //     uint8_t size;
        // };
        // struct PacketSync
        // {
        //     uint32_t objectID;
        //     uint32_t classID;
        //     char* data;
        // };
    }
}