#pragma once
#include <vector>
#include "Effect.h"

class Player; // circular reference
class EffectContainer
{
public:
	Player* caster;
	vector<Effect> effects;

	EffectContainer(Player*);
	void addEffect(Effect);
	void evalute();
};

