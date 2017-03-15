#include <Comms.h>

MessageQueue Comms::messageQueue= MessageQueue();
ServiceTable Comms::serviceTable=ServiceTable();
std::vector<Port*> Comms::portList=vector<Port*>();
PacketQueue Comms::packetQueue=PacketQueue();
Comms::Comms() {
}
