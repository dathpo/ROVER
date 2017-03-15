/*
 * Anansi.h
 *
 *  Created on: 15 Mar 2017
 *      Author: xmb14164
 */
#ifndef ANANSI_H_
#define ANANSI_H_

#include <map>
#include <string>

#include "Comms.h"
#include "Service.h"
#include "ServiceTable.h"
#include "Types.h"


class Anansi {
private:
	Service nodeService;
	Comms comms;
	ServiceTable serviceTable;
	map<string, Service> publishers;
	Service createService(byte id, string name);
public:
	Anansi();
	virtual ~Anansi();
	template<typename T>
	void advertise(byte id,string name);
	template<typename T>
	void publish(string name, T data);
	template<typename T>
	void subscribe(string name, void function(T));

	void handleAnansi();
};

#endif /* ANANSI_H_ */



/*
	usage:

	Node 1 creates a publisher that publishes 1 constantly:

	setup{
		Anansi comms;
		comms.advertise<int>(3, "MyTopic");
	}

	loop(){
		comms.handleAnansi();
		comms.publish<>("MyTopic", 1);
	}

	Node 2 creates a subscriber which prints the value of the topic MyTopic every time it receives it:

	setup(){
		Anansi comms;
		comms.subscribe<>("MyTopic", MyFunction);
	}

	loop(){
		comms.handleAnansi();
	}

	void MyFunction(int x){
		cout << "My int is: " << x;
	}
*/


