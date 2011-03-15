#include "Callback.h"

void Callback::registerCallback(string name, function<void()> callback)
{
	//this->foreach([&](Card *card){cout << "\t" << card->name << endl;});
	bool found = false;
	for (vector< pair<string, vector<function<void()>> > >::iterator it = this->callbacks.begin(); it != this->callbacks.end(); ++it) {

		if ((*it).first == name) {
			(*it).second.push_back(callback);
			found = true;
			break;
		}
	}
	if (!found) {
		vector<pair<string, vector<function<void()>> > > row;
		vector<function<void()>> callbacks;
		callbacks.push_back(callback);
		this->callbacks.push_back(make_pair(name, callbacks));
	}
}

void Callback::callback(string name)
{
	for (vector<pair<string, vector<function<void()>> > >::iterator it = this->callbacks.begin(); it != this->callbacks.end(); ++it) {
		if ((*it).first == name) {
			for (vector<function<void()>>::iterator cb = (*it).second.begin(); cb != (*it).second.end(); ++cb) {
				function<void()> callback = *cb;
				callback();
			}
			return;
		}
	}
}
