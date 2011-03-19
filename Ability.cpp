#include "Ability.h"
#include "Player.h"

Ability::Ability(Player* caster)
{
	this->caster = caster;
}

void Ability::addEffect(Effect effect)
{
	effect.parent = this;
	this->effects.push_back(effect);
}

void Ability::evalute()
{
	for (vector<Effect>::iterator it = this->effects.begin(); it != this->effects.end(); ++it) {
		it->evalute();
	}
}
