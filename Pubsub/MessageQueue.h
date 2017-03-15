#ifndef MessageQueue_h
#define MessageQueue_h
#include <iterator>
#include <deque>
#include <Message.h>
class MessageQueue {


public:
	void addMessage(Message m);
	void addPriorityMessage(Message m);
	
	deque<Message> getMessageQueue();
	Message popMessage();
	int queueSize();
};

#endif
