#ifdef NOARDUINO

#include "DummyPort.h"
#include <iostream>

Port::Port(string serial) {
	_serial = serial;
}

Port::Port(){
	_serial = "NOVAL";
}


void Port::read() {
	// Read from _serial and add to _buffer
	// TODO - implement Port::read
}

void Port::write(vector<char> serializedPacket) {
	_serial = "";
	for (char letter : serializedPacket)
    _serial += letter;
	cout<<_serial<<"\n";
}

packet_t Port::getPacketFromBuffer() {
	// Check if buffer has complete packet, if so return
	// TODO - implement Port::getPacketFromBuffer
	packet_t testPacket;
	testPacket.packetHeader.flags = 0x0;
	return testPacket;
}

#endif
