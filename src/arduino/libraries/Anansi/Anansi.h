

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
	template<typename T>
	void advertise(String name);
	template<typename T>
	void publish(String name, T data);
	template<typename T>
	void subscribe(String name, void function(T));
	
	void handleAnansi();
};

/*
	usage:
	
	Node 1 creates a publisher that publishes 1 constantly: 
	
	setup{
		Anansi comms;
		advertise<int>("MyTopic");
	}
	
	loop(){
		handleAnansi();
		publish<>("MyTopic", 1);
	}
	
	Node 2 creates a subscriber which prints the value of the topic MyTopic every time it receives it:
	
	setup(){
		Anansi comms;
		subscribe<>("MyTopic", MyFunction);
	}
	
	loop(){
		handleAnansi();
	}
	
	void MyFunction(int x){
		cout << "My int is: " << x;
	}
*/


#endif


