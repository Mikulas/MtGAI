#pragma once
#include <vector>
#include <string>

using namespace std;

// forward declaration
class Player;
class Card;

class Castable
{
private:
	bool payCost(int (*)[14], bool = false);

public:
	typedef pair<string, vector<string>> Cost;
	string mana_cost;

	virtual Cost getCost();
	void printCost();
	bool isCastable(Player*);
	void payCost(Player*);

	virtual Card* getCard() = 0;
};

