#include "Card.h"

using namespace std;

int Card::id_last = 1;

Card::Card(string name)
{
	this->id = Card::id_last;
	Card::id_last++;
	this->name = name;
}

Card Card::addRule(string rule)
{
	cout << "Adding rule " << rule << " to " << this->name << "\n";
	this->rules.push_back(rule);
	
	return *this;
}
