#ifndef PacketHandler_h
#define PacketHandler_h
#include <Types.h>

#ifdef NOARDUINO
#include <cstring>
#else
#endif

#include <Port.h>
#include <iterator>
#include <vector>
#include <Comms.h>
class PacketHandler {


public:
	packet_t createPacket(byte flags,byte messageID, byte packetID, byte targetService, byte sourceService, vector<byte> dataContent);

	void sendPacket(packet_t p, int port);

	bool crcCheck(packet_t p);

	byte calculateCrc(packet_t p);
};

#endif
