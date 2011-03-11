#include "Card.h"

using namespace std;

Card::Card(string name)
{
	this->name = name;
}

Card Card::addRule(string rule)
{
	cout << "Adding rule " << rule << " to " << this->name << "\n";
	this->rules.push_back(rule);
	
	return *this;
}
