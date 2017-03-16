#ifndef Service_h
#define Service_h

#include "Port.h"
#include <iterator>
#include <map>
#include <string>

class Service {

private:
	byte _id;
	string _name;
	std::map<int, int> _portMap; // port id to distance
	bool _local;

public:
	Service();
	Service(byte id, string name, bool local);
	virtual ~Service();
	byte getId();
	string getName();
	int getOutgoingPort();
	int getShortestDistance();
	void setPortDistance(int port, int distance);
	void flagPort(int port);
	std::map<int, int> getPortMap();
	int getShortestDistancePort();
};

#endif
