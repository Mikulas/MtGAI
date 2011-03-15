#pragma once
#include <vector>
#include <functional>
#include "Callback.h"
#include "Player.h"
#include "GameStack.h"

class Game : public Callback
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

	void registerCallbackPlayers(string, function<void()>);

	void switchPriority();
	void playByPriority();
	bool playersPassed();

	void turn();
	void play();
};
