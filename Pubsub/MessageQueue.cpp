#include <MessageQueue.h>
#include <Comms.h>
static deque<Message> _queue;
void MessageQueue::addMessage(Message m) {
	// TODO - implement MessageQueue::addMessage
	/**cout <<"adding message to queue\n";
	cout <<"message id:";
	cout << hex <<int(m._messageID);*/
	_queue.push_back(m);
}

void MessageQueue::addPriorityMessage(Message m){
	_queue.push_front(m);
}


Message MessageQueue::popMessage() {
	// TODO - implement MessageQueue::popMessage
	Message m = _queue.front();
	_queue.pop_front();
	return m;
}

//Added for testing
deque<Message> MessageQueue::getMessageQueue(){
	return _queue;
}

int MessageQueue::queueSize(){
	return _queue.size();
}