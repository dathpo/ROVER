#include <Port.h>
#include <Comms.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define STARTBYTE 0xFE
#define ENDBYTE 0xFF
int fd ;
Port::Port(int id) {
	_id = id;
	_start_last = false;
	_end_last = false;
	_packet_start_rcvd = false;
	_buffer.reserve(64);
	
	  

  if ((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0)
  {
    printf ("Unable to open serial device:\n") ;
}

}

void Port::read() {
	for(int i=0;i<_buffer.size();i++){
	
	}
  while (serialDataAvail(fd)  > 0) {
    byte b = serialGetchar (fd) ;
	 //cout << "Data on the line:";
   // cout << hex << int(b);
    if (b == STARTBYTE) {
      if (_start_last) { // byte-stuffed start byte
        if (_packet_start_rcvd) {
          _buffer.push_back(b);
          _start_last = false;
        }
      } 
      else if (_end_last) {
        if (_packet_start_rcvd) {
          // packet end
          packet_t p = getPacketFromBuffer();
			packetQueue.addPacket(p);
         	for(int i=0;i<_buffer.size();i++){
				//Serial.println(_buffer[i]);
			}
          // send the packet to the packet queue
          _buffer.clear();
          _packet_start_rcvd = false;
        }
      } 
      else {
        _start_last = true;
      }
      _end_last = false;
    } 
    else if (b == ENDBYTE) {
      if (_start_last) {
        _packet_start_rcvd = true;
        _start_last = false;
      }
      if (_end_last) { // byte-stuffed end byte
        if (_packet_start_rcvd) {
          _buffer.push_back(b);
          _end_last = false;
        }
      } 
      else {
        _end_last = true;
      }
      _start_last = false;
    } 
    else {
      if (_start_last) {
        // start of new packet
    //printf ("START OF NEW PACKET");
        _buffer.clear();
        _start_last = false;
        _packet_start_rcvd = true;
      } 
      else if (_end_last) {
        // something went wrong - we have a single end byte
        _buffer.clear();
        _end_last = false;
        _packet_start_rcvd = false;
      }
      if (_packet_start_rcvd) {
   // printf ("%c\n",b);
        _buffer.push_back(b);
      }
    }
  }
}

void Port::write(vector<byte> packet) {
    /*std::vector<byte>::const_iterator it;
	for (it = packet.begin(); it != packet.end(); ++it) {
    	_serial->write(*it);
	}*/
	 serialPutchar (fd, STARTBYTE) ;
	string s(packet.begin(), packet.end());
	byte b;
	for (int i = 0; i < s.length(); i++) {
		b = s[i];
		 serialPutchar (fd, b) ;
		if (b == STARTBYTE || b == ENDBYTE) 
			 serialPutchar (fd, b) ;
	}
	 serialPutchar (fd, ENDBYTE) ;
	 serialPutchar (fd, STARTBYTE) ;
}

packet_t Port::getPacketFromBuffer() {
	// Check if buffer has complete packet, if so return
	// TODO - implement Port::getPacketFromBuffer
	packet_header_t tempPacketHeader;
	tempPacketHeader.flags=_buffer[0] & 0x7;
	tempPacketHeader.messageID=_buffer[0] & 0x1F;
	tempPacketHeader.targetService=_buffer[1];
	tempPacketHeader.sourceService=_buffer[2];
	tempPacketHeader.packetID=_buffer[3];
	tempPacketHeader.crc=_buffer[4];
	packet_t testPacket;
	testPacket.packetHeader=tempPacketHeader;
	
	testPacket.dataContent.reserve(59);
	for(int i=5;i<_buffer.size();i++){
		
		testPacket.dataContent.push_back(_buffer[i]);
	}
	
	return testPacket;
}
