/*
 * Anansi.cpp
 *
 *  Created on: 15 Mar 2017
 *      Author: xmb14164
 */

#include "Anansi.h"

Anansi::Anansi() {
	// TODO Auto-generated constructor stub

}

Anansi::~Anansi() {
	// TODO Auto-generated destructor stub
}

Service Anansi::createService(byte id, string name) {
	serviceTable.addService(&Service(id, name, true));
}

template<typename T>
void Anansi::advertise(byte id, string name) {
	publishers[name] = Publisher<T>(id, name);
}

template<typename T>
void Anansi::publish(string name, T data) {
	if (typeid(publishers[name]) == typeid(Publisher<T>(0, name))) {
		Publisher<T> * pub = static_cast<Publisher<T>*>(&(publishers[name]));
		pub->setData(data);
	}
}

template<typename T>
void Anansi::subscribe(string name, void function(T)) {

}

void Anansi::handleAnansi() {

}

int main() {
	Anansi anansi = Anansi();
}
