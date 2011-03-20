#include "Ability.h"
#include "Card.h"
#include "Player.h"
#include "Game.h"
#include "GameStack.h"

Ability::Ability(Card* card)
{
	this->card = card;
}

Ability::Ability(Card* card, string cost, string effect)
{
	this->effects.reserve(100);
	this->card = card;
	Effect fx;
	this->cost.push_back(cost); /** @todo split the string first */
	fx.effect = effect;
	this->addEffect(fx);
}

void Ability::addEffect(Effect effect)
{
	effect.parent = this; // this must be updated very often
	this->effects.push_back(effect);
}

void Ability::evalute()
{
	for (vector<Effect>::iterator it = this->effects.begin(); it != this->effects.end(); ++it) {
		it->evalute();
	}
}

Castable::Cost Ability::getCost()
{
	return make_pair(this->mana_cost, this->cost);
}

Card* Ability::getCard()
{
	return this->card;
}
