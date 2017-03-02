

#ifndef Anansi_h
#define Anansi_h

#include <Types.h>

#include <MessageQueue.h>
#include <ServiceTable.h>
#include <iterator>
#include <vector>
#include <SerialPort.h>



class Anansi {
	
private:
	Service nodeService;
	Comms comms;
	ServiceTable serviceTable;
	Map<String,Service> publishers;

	Service createService(String name);

public:
	Anansi();	
	void advertise(String name, int type);
	void publish(String name, something);
	void subscribe(String name, void function(something));
};


#endif


