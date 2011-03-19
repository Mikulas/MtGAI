#include "Callback.h"
/*
template<typename T>
void Callback<T>::registerCallback(string name, Function callback)
{
	bool found = false;
	for (CallbackContainer::iterator it = this->callbacks.begin(); it != this->callbacks.end(); ++it) {
		if ((*it).first == name) {
			(*it).second.push_back(callback);
			found = true;
			break;
		}
	}
	if (!found) {
		vector<Function> callbacks;
		callbacks.push_back(callback);
		this->callbacks.push_back(make_pair(name, callbacks));
	}
}

template<typename T>
void Callback<T>::callback(string name, T* argument)
{
	for (CallbackContainer::iterator it = this->callbacks.begin(); it != this->callbacks.end(); ++it) {
		if ((*it).first == name) {
			for (vector<Function>::iterator cb = (*it).second.begin(); cb != (*it).second.end(); ++cb) {
				Function callback = *cb;
				callback(argument);
			}
			return;
		}
	}
}*/
