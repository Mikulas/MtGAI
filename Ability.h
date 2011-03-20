#pragma once
#include <vector>
#include "Effect.h"

// forward declaration
class Player;
class Game;
class GameStack;

class Ability
{
public:
	Player* caster;
	vector<Effect> effects;

	Ability(Player*);
	void addEffect(Effect);
	void evalute();
};

