#pragma once
#include "Callback.h"
#include "PublicZone.h"
#include "HiddenZone.h"
#include "Library.h"
#include "Hand.h"
#include "Ability.h"
#include "ManaIndex.h"

// forward declaration
class Game;

class Player : public Callback<Player>
{
public:
	int id;
	Game* game;
	PublicZone battlefield, graveyard, exile, command;
	Library library;
	Hand hand;
	bool passed;
	bool canDraw;
	int life;
	int poison;
	int landDropsLeft;
	int mana[14];

	Player();

	void setMana(Mana, int);
	int getManaSum(bool = false);

	void emptyManaPool();
	bool play(bool);
	void draw();
	void print();
};
