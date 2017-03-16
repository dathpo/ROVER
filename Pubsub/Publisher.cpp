/*
 * Publisher.cpp
 *
 *  Created on: 15 Mar 2017
 *      Author: xmb14164
 */

#include "Publisher.h"

template<class T>
Publisher<T>::Publisher(byte id, string name) {
	Service(id, name);
	_data = NULL;
}

template<class T>
Publisher<T>::~Publisher() {
	// TODO Auto-generated destructor stub
}

template<class T>
void Publisher<T>::setData(T data) {
	_data = data;
}
