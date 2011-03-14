#include "Game.h"


Game::Game()
{
	//this->stack = PublicZone();
	//this->players[0] = Player();
	//this->players[1] = Player();
	this->active = -1;
	this->priority = -1;
}

Player Game::getPriorityPlayer()
{
	if (this->priority == -1) {
		throw exception("No player has priority");
	}
	return this->players[this->priority];
}
