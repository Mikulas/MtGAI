#pragma once
#include <vector>
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
