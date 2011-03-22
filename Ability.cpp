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

	int found = cost.find_first_of(", ");
	vector<string> cost_split;
    while(found != string::npos){
        if(found > 0){
            cost_split.push_back(cost.substr(0, found));
        }
        cost = cost.substr(found + 1);
        found = cost.find_first_of(", ");
    }
    if(cost.length() > 0){
        cost_split.push_back(cost);
    }

	this->cost = cost_split;
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

bool Ability::isManaAbility()
{
	bool isManaAbility = true;
	for (vector<Effect>::iterator effect = this->effects.begin(); effect != this->effects.end(); effect++) {
		if (effect->hasTarget() || !effect->isManaEffect()) {
			isManaAbility = false;
			break;
		}
	}
	return !this->card->hasType("planeswalker") && isManaAbility; // loyal abilities are not mana abilities
}

void Ability::updatePointers()
{
	for (vector<Effect>::iterator effect = this->effects.begin(); effect != this->effects.end(); effect++) {
		effect->parent = this;
	}
}

Castable::Cost Ability::getCost()
{
	string mana_cost;
	vector<string> additional_cost;
	tr1::regex rg_mana("\\{([GURWBSXY]|[GURWBSXY]/[GURWBSXY]|\\d+)\\}");
	for (vector<string>::iterator cost = this->cost.begin(); cost != this->cost.end(); cost++) {
		if (tr1::regex_match(*cost, rg_mana)) {
			mana_cost += *cost;
		} else {
			additional_cost.push_back(*cost);
		}
	}
	return make_pair(mana_cost, additional_cost);
}

Card* Ability::getCard()
{
	return this->card;
}
