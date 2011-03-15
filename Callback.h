#pragma once
#include <vector>
#include <functional>
#include <string>

using namespace std;

class Callback
{
private:
	vector< pair<string, vector<function<void()>> > > callbacks;

public:
	void registerCallback(string, function<void()>);
	void callback(string name);
};

