#pragma once
#include <vector>
#include <functional>
#include "Callback.h"
#include "Player.h"
#include "GameStack.h"

class Game : public Callback<Game>
{
private:
	int priority;
	int active;
	
public:
	GameStack stack;

	Game();

	Player players[2];
	Player* getActivePlayer();
	Player* getInactivePlayer();
	Player* getPriorityPlayer();

	void switchPriority();
	void playByPriority(bool);
	bool playersPassed();

	void turn(int);
	void play();
	void end(int);
};
