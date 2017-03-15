/*
 * Publisher.h
 *
 *  Created on: 15 Mar 2017
 *      Author: xmb14164
 */

#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include "Service.h"

template<class T>
class Publisher: public Service {
private:
	T _data;
public:
	Publisher(byte id, string name);
	virtual ~Publisher();
	void setData(T data);
};

#endif /* PUBLISHER_H_ */
