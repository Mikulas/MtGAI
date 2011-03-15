#pragma once
#include "Callback.h"
#include "PublicZone.h"
#include "HiddenZone.h"
#include "Library.h"
#include "Hand.h"

class Player : public Callback
{
public:
	PublicZone battlefield, graveyard, stack, exile, command;
	Library library;
	Hand hand;
	bool passed;
	bool canDraw;
	int life;
	int poisson;

	Player();

	void play();
	void draw();
	void print();
};

