#pragma once
#include <vector>
#include <string>
#include <regex>
#include "Effect.h"
#include "Castable.h"

// forward declaration
class Card;
class Player;
class Game;
class GameStack;

class Ability : public Castable
{
public:
	Card* card;
	Player* caster; // caster may not be the controller of the card
	vector<Effect> effects;

	vector<string> cost;

	bool isManaAbility();
	virtual Castable::Cost getCost();
	virtual Card* getCard();
	void updatePointers();

	Ability(Card*);
	Ability(Card*, string, string);
	void addEffect(Effect);
	void evalute();
};

