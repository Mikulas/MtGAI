#pragma once
#include <vector>
#include <string>
#include <assert.h>

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
	
	virtual Cost getCost() = 0;
	void printCost();
	bool isCastable(Player*);
	void payCost(Player*);

	virtual Card* getCard() = 0;
};

