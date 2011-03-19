#include "EffectContainer.h"

EffectContainer::EffectContainer(Player* caster)
{
	this->caster = caster;
}

void EffectContainer::addEffect(Effect effect)
{
	effect.parent = this;
	this->effects.push_back(effect);
}

void EffectContainer::evalute()
{
	for (vector<Effect>::iterator it = this->effects.begin(); it != this->effects.end(); ++it) {
		it->evalute();
	}
}
