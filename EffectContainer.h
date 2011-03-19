#pragma once
#include <vector>
#include "Effect.h"

// forward declaration
class Player;

class EffectContainer
{
public:
	Player* caster;
	vector<Effect> effects;

	EffectContainer(Player*);
	void addEffect(Effect);
	void evalute();
};

