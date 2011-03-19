#pragma once
#include "Callback.h"
#include "PublicZone.h"
#include "HiddenZone.h"
#include "Library.h"
#include "Hand.h"
#include "GameStack.h"

class Player : public Callback<Player>
{
public:
	GameStack* stack;
	PublicZone battlefield, graveyard, exile, command;
	Library library;
	Hand hand;
	bool passed;
	bool canDraw;
	int life;
	int poison;
	int landDropsLeft;
	int mana[11]; // Forest, Island, Mountain, Plains, Swamp, Snow-Forest, Snow-Island, Snow-Mountain, Snow-Plains, Snow-Swamp, Colorless

	Player();

	void emptyManaPool();
	void play(bool);
	void draw();
	void print();
};
