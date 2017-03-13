#include "ResourceDiscovery.cpp"
include <stdio.h>

int main(){
	ResourceDiscovery rd;
	rd.advertise();
	vector<byte> testContent;
	testContent.push_back(0x10);
	ServiceTable t;
	Message m1((byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x03, (byte) 0x00, (vector<bytes>) t);
	rd.receive(m1);	
}