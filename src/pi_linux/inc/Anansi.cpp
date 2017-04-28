/*
 * Anansi.cpp
 *
 *  Created on: 15 Mar 2017
 *      Author: xmb14164
 */

#include <Anansi.h>

Anansi::Anansi(byte nodeId) {
	_comms = Comms();
	_serviceTable = ServiceTable();
	_nodeService = createService(nodeId, "nodeService" + nodeId);
	_publishers = map<string, Service>();
}

Anansi::~Anansi() {
	// TODO Auto-generated destructor stub
}

Service Anansi::createService(byte id, string name) {
	Service service(id, name, true); //* service = new Service(id, name, true);
	_serviceTable.addService(service);
	return service;
}

template<typename T>
void Anansi::advertise(byte id, string name) {
	_publishers[name] = Publisher<T>(id, name);
}

template<typename T>
void Anansi::publish(string name, T data) {
	if (typeid(_publishers[name]) == typeid(Publisher<T>(0, name))) {
		Publisher<T> * pub = static_cast<Publisher<T>*>(&(_publishers[name]));
		pub->setData(data);
	}
}

template<typename T>
void Anansi::subscribe(string name, void function(T)) {

}

void Anansi::handleAnansi() {

}
