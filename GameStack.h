#pragma once
#include <vector>
#include "Card.h"
#include "PublicZone.h"
#include "EffectContainer.h"

class GameStack : public PublicZone
{
public:
	vector<EffectContainer> effects;
	vector<int> queue;
	bool isEmpty();

	void addCard(Card);
	void addEffect(EffectContainer);
	void execute();
};
