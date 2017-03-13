#ifndef Service_h
#define Service_h

#ifdef NOARDUINO
#include <DummyPort.h>
#else
#include <Port.h>
#endif
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
	Service(byte id, string name, bool local);
	~Service();
	byte getId();
	string getName();
	int getOutgoingPort();
	int getShortestDistance();
	void setPortDistance(int port, int distance);
	void flagPort(int port);
	std::map<int, int> getPortMap();
};

#endif
