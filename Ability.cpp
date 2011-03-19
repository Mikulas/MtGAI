#include "Ability.h"
#include "Player.h"
#include "Game.h"
#include "GameStack.h"

Ability::Ability(Player* caster)
{
	this->caster = caster;
}

void Ability::addEffect(Effect effect)
{
	effect.parent = &(this->caster->game->stack.abilities.back());
	this->effects.push_back(effect);
}

void Ability::evalute()
{
	for (vector<Effect>::iterator it = this->effects.begin(); it != this->effects.end(); ++it) {
		it->evalute();
	}
}
