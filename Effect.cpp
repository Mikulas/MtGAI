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

/*	//Player caster = this->parent->caster;
	cout << "evaluating effect: " << this->effect << endl;
	//tr1::regex rg_mana = tr1::regex("Add ((\{[GURWB]\})+|\{(\d+)\}|one mana of any color) to your mana pool");
	tr1::regex rg_sentence = tr1::regex("Add (.*?) to your mana pool");
	tr1::regex rg_mana = tr1::regex("\\{[GURWB])+\\}|\\{d+\\}|one mana of any color");
	tr1::cmatch res;
	tr1::regex_iterator(this->effect.begin(), this->effect.end(), rg_mana);
	if (tr1::regex_match(this->effect.c_str(), res, rg_sentence)) {
		if (res[1] == "one mana of any color") {
			//cout << "caster property: landdropsleft = " << caster->landDropsLeft << endl;
		}
	}*/
}
