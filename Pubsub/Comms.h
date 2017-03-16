#ifndef Comms_h
#define Comms_h

#include "Types.h"
#include "Port.h"
#include "MessageQueue.h"
#include "ServiceTable.h"
#include "PacketQueue.h"

#include <iterator>
#include <vector>

class Comms {
public:
	static MessageQueue messageQueue;
	static ServiceTable serviceTable;
	static vector<Port*> portList;
	static PacketQueue packetQueue;
	Comms();
};

#endif
