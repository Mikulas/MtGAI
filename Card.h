#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Card
{
private:
	
public:
	vector<string> rules;
	string name;
	
	Card(string);
	Card addRule(string);
};
