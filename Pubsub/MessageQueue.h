#ifndef MessageQueue_h
#define MessageQueue_h

#include "Message.h"
//#include "Comms.h"
#include <iterator>
#include <deque>

class MessageQueue {
public:
	void addMessage(Message m);
	void addPriorityMessage(Message m);

	deque<Message> getMessageQueue();
	Message popMessage();
	int queueSize();
};

#endif
