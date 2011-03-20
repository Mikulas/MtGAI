#pragma once
#include <vector>
#include <string>

using namespace std;

// forward declaration
class Player;

class Castable
{
private:
	bool payCost(int (*)[14]);

public:
	typedef pair<string, vector<string>> Cost;
	string mana_cost;

	virtual Cost getCost();
	void printCost();
	bool isCastable(Player*);
	void payCost(Player*);
};

