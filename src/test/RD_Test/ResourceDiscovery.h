#ifndef ResourceDiscovery_h
#define ResourceDiscovery_h

#include <Service.h>
#include <ServiceTable.h>
#include <iterator>
#include <map>

class ResourceDiscovery {

public:
	ResourceDisovery();
	~ResourceDiscovery();
	void advertise();
	void receive(Message m);
};

#endif
	