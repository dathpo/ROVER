#include <ResourceDiscovery.h>
#include <HardwareSerial.h>


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
	
}

void receive(Message m){

}

