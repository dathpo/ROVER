#ifndef SerialPort_h
#define SerialPort_h

#include <Port.h>
#include <iterator>
#include <HardwareSerial.h>
class SerialPort : public Port{

public:

	SerialPort(int id, HardwareSerial *serial);
	void read();

	void write(vector<byte> serializedPacket);

	packet_t getPacketFromBuffer();

};

#endif
