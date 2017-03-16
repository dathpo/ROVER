#ifndef PacketQueue_h
#define PacketQueue_h

#include "Types.h"
#include "Message.h"
#include "Port.h"
#include "Comms.h"
#include "PacketHandler.h"

#include <iostream>
#include <iterator>
#include <deque>

class PacketQueue {

	deque<packet_t> _queue;

public:
	PacketQueue();
	void addPacket(packet_t p);

	void popPacket();

	Message checkPacketQueue();

	Message buildMessage(vector<packet_t> p);
	
};

#endif
