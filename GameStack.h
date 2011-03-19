#pragma once
#include <vector>
#include "Card.h"
#include "PublicZone.h"
#include "Ability.h"

class GameStack : public PublicZone
{
public:
	vector<Ability> abilities;
	vector<int> queue;
	bool isEmpty();

	void addCard(Card);
	void addAbility(Ability);
	void execute();
};
