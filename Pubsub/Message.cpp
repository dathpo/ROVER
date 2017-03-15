#include <Message.h>
#include <stdlib.h>


#include <PacketHandler.h>
/*
* NEED TO WORK OUT HOW TO HAVE STRUCTRE BUT NOT POINTING
* TO THE SAME STRUCTURE EACH TIME, BUT A DIFFERENT ONE
*/


Message::Message(byte messageID, byte targetService, byte sourceService, byte typeOfMessage, byte messageBitfields, vector<byte> bodyContent) {
	//printf("%d",int(targetService));
	_messageID = messageID;
	_targetService = targetService;
	_sourceService = sourceService;
	_bodyContent = bodyContent;
	
	//Integer division always rounds down so adding one to give desired result

	//_messageHeader.numOfPacketsInMessage = (byte)((MESSAGE_HEADER_SIZE + _bodyContent.size())/PACKET_CONTENT_SIZE) + 1;
	_typeOfMessage = (byte)  typeOfMessage;
	_messageBitfields = (byte) messageBitfields;


}
vector<packet_t> Message::toPackets() {
	// Generates bytestream 
	deque<byte> bytes; 
	//bytes.push_back(_messageHeader.numOfPacketsInMessage);
	bytes.push_back(_typeOfMessage);
	bytes.push_back(_messageBitfields);
	bytes.insert(bytes.end(), _bodyContent.begin(), _bodyContent.end());
	vector<packet_t> packets;
	PacketHandler handler;
	 
	
	for(int pNo; bytes.size() > 0; pNo++){
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
	if (_typeOfMessage == MT_PASS_ON) {
		//initate ResourceDiscover and pass on
		//printf("This is an RD message to pass on.\n");
	}
	else if (_typeOfMessage == MT_ADVERTISE) {
		//Advertisement
		//printf("This is an advertise message.\n");
	}
	else if (_typeOfMessage == MT_STOP) {
		//Inititate Resource Discovery and Stop
		//printf("This is a RD message, not to pass on!\n");
	}
	else {
		//DEBUG
		//printf("This is not a resource discovery message.\n");
	}
	//fflush(stdout);
}

