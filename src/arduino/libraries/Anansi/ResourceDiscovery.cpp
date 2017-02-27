#include <ResourceDiscovery.h>
#include <HardwareSerial.h>

#include <Message.h>
ResourceDiscovery::ResourceDiscovery() {

}


ResourceDiscovery::~ResourceDiscovery() {

}

/*
 * Copies service table for this node and adds 1 to all distances.
 * Serialises the copy of this service table and sends to all ports.
*/
void advertise(){
	ServiceTable t = serviceTable;
	for (std::map<byte, Service*>::iterator it = t.begin(); it != t.end(); ++it) {
		Service s = t.getService(it->first);
		std::map<int, int> portMap = s.getPortMap();
		for(std::map<int, int>::iterator it2 = portMap.begin(); it2 != portMap.end(); ++it2){
			s.setPortDistance(it2->first,((it2->second) + 1));
		}
	}
	sendToAll((vector<byte) t);
}

/*
 *
 *
*/
void receive(Message m){
	ServiceTable t = (ServiceTable) m->_messageContent;
	_table.mergeTable(t);
	if(_table.toString != t.toString()){
		advertise();
	}
}

void sendToAll(vector<byte> messageContent){
	byte messageID = 0x00;
	byte targetService = 0x00;
	byte sourceService = 0x01;
	byte typeOfMessage = 00010;
	byte messageBitFields = 000;
	Message m (messageID, targetService, sourceService, typeOfMessage, messageBitFields);
	for(std::map<int, int>::iterator it = portMap.begin(); it != portMap.end(); ++it){
		m.sendMessage(it->first);
	}
}