#pragma once
#include <vector>
#include <string>
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

	virtual Castable::Cost getCost();
	virtual Card* getCard();

	Ability(Card*);
	Ability(Card*, string, string);
	void addEffect(Effect);
	void evalute();
};

