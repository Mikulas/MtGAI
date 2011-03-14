#pragma once
#include "PublicZone.h"
#include "HiddenZone.h"
#include "Library.h"
#include "Hand.h"

class Player
{
public:
	PublicZone battlefield, graveyard, stack, exile, command;
	Library library;
	Hand hand;

	Player();

	void draw();
	void print();
};

