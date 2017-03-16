#include "PacketHandler.h"

//having to include cstring to run
packet_t PacketHandler::createPacket(byte flags,byte messageID, byte packetID, byte targetService, byte sourceService, vector<byte> dataContent) {
	packet_t packet;
	packet_header_t packetHeader;
	packetHeader.flags=flags & 0x7;
	packetHeader.messageID=messageID & 0x1F;
	packetHeader.targetService=targetService;
	packetHeader.sourceService=sourceService;
	packetHeader.packetID=packetID;
	packetHeader.crc=0x0;
	packet.packetHeader=packetHeader;
	packet.dataContent=dataContent;
	packet.packetHeader.crc=calculateCrc(packet);
	return packet;
	
}

void PacketHandler::sendPacket(packet_t p, int port) {
	//cout <<"Send Packet Back";
	vector<byte> serializedPacket;
	
	byte size= sizeof(p.packetHeader)+p.dataContent.size(); //get total packet size
	byte b[64]; //ready memory for byte array cast
	memcpy(b, &p, sizeof(p.packetHeader));//copy header to first part of byte array
	memcpy(b+ sizeof(p.packetHeader), &p.dataContent[0], p.dataContent.size());//copy header to first part of byte array
	//copy data content to remaining part of byte array
	
	//serializedPacket.push_back (0xFE); //ADD START BYTE
	 //Byte Stuffing now done in PORT this isnt needed anymore?
	for( int index=0; index<size; index++){
		serializedPacket.push_back (b[index]);
		/*if (b[index]==0xFE){
			serializedPacket.push_back (0xFE);
		}else if(b[index]==0xFF){
			serializedPacket.push_back (0xFF);
		}*/
	}
	
	//serializedPacket.push_back (0xFF); //ADD END BYTE(s)
	//serializedPacket.push_back(0xFE);

	Port* transferPort = Comms::portList[port];
	transferPort->write(serializedPacket);
	//std::cout <<"Printing byte stuffed packet1copy" <<endl;
	//for (std::vector<byte>::const_iterator i = serializedPacket.begin(); i != serializedPacket.end(); ++i)
	//	cout << hex << int(*i) << ' ';
	
	
}

bool PacketHandler::crcCheck(packet_t p) {
	
	packet_t pCopy = p;
	pCopy.packetHeader.crc=0;
	return (p.packetHeader.crc==calculateCrc(pCopy));
	
}


byte PacketHandler::calculateCrc(packet_t p) {
	// CRC8 calculator.
	// Credit to Dallas/Maxim
	byte crc = 0x00;
	byte size= sizeof(p.packetHeader)+p.dataContent.size(); //get total packet size
	byte b[64]; //ready memory for byte array cast
	memcpy(b, &p, sizeof(p.packetHeader));//copy header to first part of byte array
	int counter=sizeof(p.packetHeader);
	for (std::vector<byte>::const_iterator i = p.dataContent.begin(); i != p.dataContent.end(); ++i)
		b[counter]=*i;
		counter++;
	//cout << "Getting data content size" << endl;
	//cout << hex << p.dataContent.size() << endl;
	for (int index = 0; index<size; index++) {
		byte extract = b[index];
		for (byte tempI = 8; tempI; tempI--) {
			byte sum = (crc ^ extract) & 0x01;
			crc >>= 1;
			if (sum) {
				crc ^= 0x8C;
			}
			extract >>= 1;
		}
	}
	return crc;
}



