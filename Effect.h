#pragma once
#include <vector>
#include <string>
#include "ManaIndex.h"
#include "Castable.h"

// forward declarations
class Card;
class Ability;
class Player;

using namespace std;

class Effect
{
public:
	string effect;
	Ability *parent;

	Effect();
	
	vector<Player*> target_players;
	vector<Card*> target_cards;
	vector<Effect*> target_effects;

	void setTarget(Player*);
	void setTarget(Card*);
	void setTarget(Effect*);

	void evalute();
};
