#include "Message.h"
#include "PacketHandler.cpp"

using namespace std;

byte _messageID;
byte _targetService;
byte _sourceService;
vector<byte> _bodyContent;
message_header_t _messageHeader;

Message::Message(byte messageID, byte targetService, byte sourceService, byte typeOfMessage, byte messageBitfields, vector<byte> bodyContent) {

	_messageID = messageID;
	_targetService = targetService;
	_sourceService = sourceService;
	_bodyContent = bodyContent;
	
	//Integer division always rounds down so adding one to give desired result
	_messageHeader.numOfPacketsInMessage = ((MESSAGE_HEADER_SIZE + _bodyContent.size())/PACKET_CONTENT_SIZE) + 1;
	_messageHeader.typeOfMessage = typeOfMessage;
	_messageHeader.messageBitfields = messageBitfields;
}

vector<packet_t> Message::toPackets() {
	// Generates bytestream 
	deque<byte> bytes; 
	bytes.push_back(_messageHeader.numOfPacketsInMessage);
	bytes.push_back(_messageHeader.typeOfMessage);
	bytes.push_back(_messageHeader.messageBitfields);
	bytes.insert(bytes.end(), _bodyContent.begin(), _bodyContent.end());
	vector<packet_t> packets;
	PacketHandler handler;
	 
	for(int pNo = 0; bytes.size() > 0; pNo++){
		vector<byte> tempByteVector;
		packet_t tempPacket;
		for(int i = 0; i < PACKET_CONTENT_SIZE; i++){
			tempByteVector.push_back(bytes[i]);
			bytes.erase(bytes.begin());
		}
		//Flags currently defaulted to 0  as not implemented yet
		tempPacket = handler.createPacket(000, _messageID, pNo, _targetService, _sourceService, tempByteVector);
		packets.push_back(tempPacket);
	}
	return packets;
}


//if resource discover 2/7 pass on if not serial.println
void Message::readMessage() {

#define MT_PASS_ON 0x07
#define MT_ADVERTISE 0x02
#define MT_STOP 0x08

	// TODO - implement Message::readMessage
	if (_messageHeader.typeOfMessage == 0x07) {
		//initate ResourceDiscover and pass on
		printf("This is an RD message to pass on.\n");
	}
	else if (_messageHeader.typeOfMessage == MT_ADVERTISE) {
		//Advertisement
		printf("This is an advertise message.\n");
	}
	else if (_messageHeader.typeOfMessage == MT_STOP) {
		//Inititate Resource Discovery and Stop
		printf("This is a RD message, not to pass on!\n");
	}
	else {
		//DEBUG
		printf("This is not a resource discovery message.\n");
	}
}
