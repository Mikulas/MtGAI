#pragma once
#include <vector>
#include <string>
#include "Card.h"
#include "ManaIndex.h"

// forward declarations
class Ability;
class Player;

class Effect
{
public:
	string effect;

	Ability *parent;
	
	vector<Player*> target_players;
	vector<Card*> target_cards;
	vector<Effect*> target_effects;

	void setTarget(Player*);
	void setTarget(Card*);
	void setTarget(Effect*);

	void evalute();
};
