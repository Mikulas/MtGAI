#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Card
{
private:
	static int id_last;
	int id;

public:
	vector<string> rules;
	string name;
	
	Card(string);
	Card addRule(string);

	bool Card::operator== (Card card) {
		return this->id == card.id;
	}
};
