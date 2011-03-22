#pragma once
#include <vector>
#include <functional>
#include <string>

using namespace std;

template<typename T>
class Callback
{
public:
	typedef function<void(T*)> Function;
	typedef vector< pair<string, vector<Function>> > CallbackContainer;
	
	void registerCallback(string name, Function callback)
	{
		bool found = false;
		for (CallbackContainer::iterator container = this->callbacks.begin(); container != this->callbacks.end(); ++container) {
			if (container->first == name) {
				container->second.push_back(callback);
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

	void callback(string name, T* argument)
	{
		for (CallbackContainer::iterator container = this->callbacks.begin(); container != this->callbacks.end(); ++container) {
			if (container->first == name) {
				for (vector<Function>::iterator cb = container->second.begin(); cb != container->second.end(); ++cb) {
					Function call = *cb;
					call(argument);
				}
				return;
			}
		}
	}


private:
	CallbackContainer callbacks;
};
