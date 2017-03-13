#include <ServiceTable.h>
#include <HardwareSerial.h>
ServiceTable::ServiceTable() {
	
}

ServiceTable::~ServiceTable() {
}

/* Returns the service with a given id. */
Service* ServiceTable::getService(byte id) {

		//Serial.println(_table.size());
		Serial.println("entered getService");
		
		Serial.println(_table.size());
	if(_table.size()>id){
		Serial.println(id);
	return _table[id];
	}else{ static Service newService(0,"0",false); 
		Serial.println("Failure"); 
		return &newService;}
}

/* Adds a service to the look-up table. Existing service will be merged into if present. */
void ServiceTable::addService(Service *s) {
	Serial.println("Added a service");
	int id = s->getId();
	if (_table.find(id) == _table.end()) { // Service is not yet in table
		_table[id] = s;
	} else { // Service is already in table, so merge port maps
		std::map<int, int> portMap = s->getPortMap();
		for (std::map<int, int>::iterator it = portMap.begin(); it != portMap.end(); ++it) {
			_table[id]->setPortDistance(it->first, it->second);
		}
	}
}

/* Merges another service table into this one. */
void ServiceTable::mergeTable(ServiceTable t) {
	std::map<byte, Service*> otherTable = t.getTable();
	for (std::map<byte, Service*>::iterator it = otherTable.begin(); it != otherTable.end(); ++it) {
		addService(it->second);
	}
}

/* Returns the look-up table. */
std::map<byte, Service*> ServiceTable::getTable() {
	return _table;
}

string ServiceTable::toString() {
	string str = "Table: ";
	for (std::map<byte, Service*>::iterator it = _table.begin(); it != _table.end(); ++it) {
		str += it->second->getName();
	}
	return str;
}
