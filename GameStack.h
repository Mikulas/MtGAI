#pragma once
#include <vector>
#include "Card.h"
#include "PublicZone.h"
#include "Ability.h"

// forward declaration
class Player;

class GameStack : public PublicZone
{
public:
	vector<Ability> abilities;
	vector<int> queue;
	bool isEmpty();

	virtual void addCard(Card);
	void addAbility(Ability);
	void execute();
};
