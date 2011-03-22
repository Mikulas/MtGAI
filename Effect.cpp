#include "Effect.h"
#include "Card.h"
#include "Ability.h"
#include "Player.h"

Effect::Effect()
{
	this->target_players.reserve(10);
	this->target_cards.reserve(10);
	this->target_effects.reserve(10);
}

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

bool Effect::hasTarget()
{
	return !(this->target_players.size() == this->target_effects.size() == this->target_players.size() == 0);
}

bool Effect::isManaEffect()
{
	tr1::regex rg_pool("[Aa]dd[^.]*mana pool");
	return tr1::regex_search(this->effect, rg_pool);
}

void Effect::evalute()
{
	Player* caster = this->parent->caster;
	cout << "evaluating effect: " << this->effect << endl;
	
	tr1::regex rg_sentence("Add (.*?) to your mana pool");
	tr1::regex rg_mana("\\{[GURWB]\\}|\\{\\d+\\}|one mana of any color");
	tr1::cmatch res;
	const tr1::sregex_token_iterator end;
	if (tr1::regex_match(this->effect.c_str(), res, rg_sentence)) {
		string match(res[1]);
		for (tr1::sregex_token_iterator it(match.begin(), match.end(), rg_mana); it != end; it++) {
			if (res[1] == "one mana of any color") {
				cout << "mana of what color do you want to add to your mana pool?" << endl;
				// IMPLEMENT
			} else if (res[1] == "{G}") {
				caster->setMana(Forest, 1);
			} else if (res[1] == "{U}") {
				caster->setMana(Island, 1);
			} else if (res[1] == "{R}") {
				caster->setMana(Mountain, 1);
			} else if (res[1] == "{W}") {
				caster->setMana(Plains, 1);
			} else if (res[1] == "{B}") {
				caster->setMana(Swamp, 1);
			} else {
				tr1::regex rg_colorless("\\{(\\d+)\\}");
				tr1::cmatch amount;
				tr1::regex_match(string(res[1]).c_str(), amount, rg_colorless);
				caster->setMana(Colorless, atoi(string(amount[1]).c_str()));
			}
		}
	}
}
