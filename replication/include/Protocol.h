namespace uqac::replication
{
    enum class PacketType : uint8_t
    {
        Hello = 0x00,
        Sync = 0x01,
        Bye = 0x02,
        PacketType_Max
    }
}