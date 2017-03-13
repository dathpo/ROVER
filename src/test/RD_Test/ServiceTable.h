#ifndef ServiceTable_h
#define ServiceTable_h

#include <Service.h>
#include <MessageQueue.h>
#include <iterator>
#include <map>

class ServiceTable {

private:
	std::map<byte, Service*> _table;

public:
	ServiceTable();
	~ServiceTable();
	Service* getService(byte id);
	void addService(Service *s);
	void mergeTable(ServiceTable t);
	std::map<byte, Service*> getTable();
	string toString();
};

#endif
