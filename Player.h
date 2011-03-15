#pragma once
#include "Callback.h"
#include "PublicZone.h"
#include "HiddenZone.h"
#include "Library.h"
#include "Hand.h"
#include "GameStack.h"

class Player : public Callback
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
	// how should I store mana?
	int mana[10]; // Forest, Island, Mountain, Plains, Swamp, Snow-Forest, Snow-Island, Snow-Mountain, Snow-Plains, Snow-Swamp

	Player();

	void emptyManaPool();
	void play(bool);
	void draw();
	void print();
};
