#include "Effect.h"

void Effect::setTarget(Player* player)
{
	this->target_players.push_back(player);
}

void Effect::setTarget(Card* card)
{
	this->target_cards.push_back(card);
}

void Effect::setTarget(Effect* effect)
{
	this->target_effects.push_back(effect);
}

void Effect::evalute()
{
	cout << "evalutaing effect: " << this->effect << endl;
}
