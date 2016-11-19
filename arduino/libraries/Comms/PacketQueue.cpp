#include "PacketQueue.h"
#include "Types.h"

deque<packet_t> packetQueue;
void PacketQueue::addPacket(packet_t p) {
	packetQueue.push_back(p);
}

packet_t PacketQueue::popPacket() {
	return packetQueue.pop_front;
}

Message PacketQueue::checkPacketQueue() {

	vector<packet_t> messageTrack; //keep track of packets which could potentially create entire message

	if (packetQueue.front.packetHeader.packetID == 1) { //if the first packet in buffer is the first packet of message
		messageTrack.push_back(packetQueue.front); //add it to the potential packets list
		if (packetQueue.size() >= packetQueue.front.dataContent.at(0)) { //if there are enough packets to build an entire message in the queue
			int counter = 1; //keep track of number of packets in message
			for (int i = 0; i < packetQueue.size(); i++) { 
				if (packetQueue.at(i).packetHeader.messageID == packetQueue.front.packetHeader.messageID) { //if packets are part of same message
					counter++;
					messageTrack.push_back(packetQueue.at(i)); //add potential packet
				}
			}
			if (counter == packetQueue.front.dataContent.at(0)) { //if all packets that could make up the message are present
				return buildMessage(messageTrack); //build the message and return it.
			}
		}
	}
	else {
		popPacket(); //if first packet in queue is not the first packet in message. Something has gone wrong, so pop it.
	}
	return;

}

void PacketQueue::setPacketQueue(deque<packet_t> p) { //set packet queue for debug purposes.

	packetQueue = p;
}

Message PacketQueue::buildMessage(vector<packet_t> p) {
	byte messageID = p.at(0).packetHeader.messageID; //Grab data about Message from first packet
	byte targetService = p.at(0).packetHeader.targetService;
	byte sourceService = p.at(0).packetHeader.sourceService;
	byte typeOfMessage = p.at(0).dataContent.at(1) & 0xF8;
	byte messageBitfields = p.at(0).dataContent.at(1) & 0x7;
	vector<byte> bodyContent;

	for (int i = 0; i < p.size(); i++) { //grab body content from each of the packets and push it to bodycontent var
		if (i == 0) {
			int y = 2; //if this is first packet, skip message header
		}
		else {
			int y = 0;
		}
		for (int y = 0; y < p.at(i).dataContent.size(); y++) {
			bodyContent.push_back(p.at(i).dataContent.at(y));  //add body content to vector var;
		}
	}
	Message builtMessage = Message(messageID, targetService, sourceService, typeOfMessage, messageBitfields, bodyContent);

	return builtMessage;
}