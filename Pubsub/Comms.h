#ifndef Comms_h
#define Comms_h

#include <Types.h>
#ifndef NOARDUINO
#include <Port.h>

#else
#include <Port.h>

#endif
#include <MessageQueue.h>
#include <ServiceTable.h>
#include <iterator>
#include <vector>
#include <SerialPort.h>


//extern PacketHandler handle;
#include <PacketQueue.h>

class Comms {


public:

static MessageQueue messageQueue;
static ServiceTable serviceTable;
static vector<Port*> portList;
static PacketQueue packetQueue;
	Comms();
};


#endif
