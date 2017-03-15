#ifndef Port_h
#define Port_h
#include <iterator>
#include <vector>
#include "Types.h"

class Port {


public:
	vector<byte> _buffer;

	bool _start_last;
	bool _end_last;
	bool _packet_start_rcvd;
	 int _id;
	virtual void read() =0;

	virtual void write(vector<byte> serializedPacket) =0;

	virtual packet_t getPacketFromBuffer() = 0;

};

#endif