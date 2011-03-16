#pragma once
#include <vector>
#include <string>
#include "Card.h"

class Player; // circular reference
class Effect
{
public:
	string effect;

	vector<Player*> target_players;
	vector<Card*> target_cards;
	vector<Effect*> target_effects;

	void setTarget(Player*);
	void setTarget(Card*);
	void setTarget(Effect*);

	void evalute();
};

