#include <Service.h>

Service::Service(byte id, string name, bool local) {
	_id = id;
	_name = name;
	_local = local;

}

Service::~Service() {}


/* Returns the ID number of the service. */
byte Service::getId() {
	return _id;
}

/* Returns the name of the service. */
string Service::getName() {
	return _name;
}



/* Returns the port with the shortest associated distance to this service. 
Requires that there is an outgoing port - check getShortestDistance > 0 first. */

int Service::getOutgoingPort() {

	return _portMap[_id];
}

/* Returns the shortest distance associated with this service. */
int Service::getShortestDistance() {

	int d = -1;
			printf("got to here d=-1");
		fflush(stdout);
	for (std::map<int, int>::iterator it = _portMap.begin(); it != _portMap.end(); ++it) {
				//cout<<_name;
		fflush(stdout);
		if (d < 0 || it->second < d) {

			d = it->second;
		}
	}
			printf("got to here returning d");
		fflush(stdout);
	return d;
}

int Service::getShortestDistancePort() {
	/*NEED TO ADD INPUT VALIDATION TO ENSURE THAT WE RETURN A PORT IN THE LIST THAT ACTUALLY EXISTS!!*/
	int d = -1;
	for (std::map<int, int>::iterator it = _portMap.begin(); it != _portMap.end(); ++it) {
		if (d < 0 || it->second < d) {
			
			d = it->first; 
			
		}
	}

	return d;
}



/* Sets the associated distance for this service on a particular port. Will only 
overwrite an existing entry if the new distance is less than the old distance.
Or adds it if the port doesnt already exist. */
void Service::setPortDistance(int port, int distance) {
	if (_portMap.find(port) == _portMap.end()
		|| _portMap[port] > distance) {
		_portMap[port] = distance;
	}
}

/* Returns the port map */
std::map<int, int> Service::getPortMap() {
	return _portMap;
}
