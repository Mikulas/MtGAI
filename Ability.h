#pragma once
#include <vector>
#include <string>
#include "Effect.h"

// forward declaration
class Card;
class Player;
class Game;
class GameStack;

class Ability
{
public:
	Card* card;
	Player* caster; // caster may not be the controller of the card
	vector<Effect> effects;

	vector<string> cost;

	Ability(Card*);
	Ability(Card*, string, string);
	void addEffect(Effect);
	void evalute();
};

