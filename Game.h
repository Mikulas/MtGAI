#pragma once
#include "Player.h"
#include "PublicZone.h"

class Game
{
private:
	int priority;
	int active;
	
public:
	PublicZone stack;

	Game();

	Player players[2];
	Player getActivePlayer();
	Player getPriorityPlayer();
};
