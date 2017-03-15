#ifdef NOARDUINO
#ifndef DummyPort_h
#define DummyPort_h
#include <iterator>
#include <vector>
#include "Types.h"

class Port {

private:
	vector<byte> _buffer;
	string _serial;

public:
	Port(string serial);
	Port();
	int id;
	void read();

	void write(vector<char> serializedPacket);

	packet_t getPacketFromBuffer();

};

#endif
#endif
