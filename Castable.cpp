#include "Castable.h"
#include "Player.h"
#include "Card.h"

void Castable::printCost()
{
	Cost cost = this->getCost();
	cout << cost.first;
	for (vector<string>::iterator it = cost.second.begin(); it != cost.second.end(); ++it) {
		cout << ", " << *it;
	}
}

bool Castable::isCastable(Player* caster)
{
	return this->payCost(&(caster->mana));
}

void Castable::payCost(Player* caster)
{
	if (!this->payCost(&(caster->mana), true))
		throw exception("Player managed to play a noncastable spell");
}

bool Castable::payCost(int (*pointer)[14], bool paying)
{
	int mana[14];
	for (int i = 0; i < sizeof(*pointer) / sizeof(int); i++) {
		mana[i] = (*pointer)[i];
	}
	tr1::regex rg_mana("(\\d+)?([GURWBS]|\\{[GURWB]{2}\\}|\\{(X|Y)\\})*");
	tr1::cmatch res;
	string mana_cost = this->getCost().first;
	if (tr1::regex_match(mana_cost.c_str(), res, rg_mana)) {
		int colorless = atoi(string(res[1]).c_str());
		tr1::regex rg_color("[GURWBS]|\\{GURWB\\}");
		tr1::sregex_token_iterator end;
		string match(res[2]);
		for (tr1::sregex_token_iterator it(match.begin(), match.end(), rg_color); it != end; it++) {
			if (*it == "G") mana[Forest] -= 1;
			else if (*it == "U") mana[Island] -= 1;
			else if (*it == "R") mana[Mountain] -= 1;
			else if (*it == "W") mana[Plains] -= 1;
			else if (*it == "B") mana[Swamp] -= 1;
			else if (*it == "S") mana[Snow] -= 1;
			else {
				cout << "choice cost not implemented";
				return false;
			}
		}
		
		int colored_mana[] = {Forest, Island, Mountain, Plains, Swamp};
		for (int i = 0; i < 5; i++) {
			while (mana[i] < 0) {
				if (mana[colored_mana[i] + 5] > 0) { // spend snow mana
					mana[i] += 1;
					mana[colored_mana[i] + 5] -= 1;
				} else if (mana[Multicolor] > 0) { // spend multicolor mana
					mana[colored_mana[i]] += 1;
					mana[Multicolor] -= 1;
				} else if (mana[SnowMulticolor] > 0) { // spend multicolor snow mana
					mana[colored_mana[i]] += 1;
					mana[SnowMulticolor] -= 1;
				} else {
					return false;
				}
			}
		}
		while (mana[Snow] < 0) { /** @todo fix me, must predict what color is the best to be spend */
			for (int i = 0; i < 5; i++) {
				if (mana[colored_mana[i] + 5] > 0) {
					mana[Snow] += 1;
					mana[colored_mana[i] + 5] -= 1;
				}
				break;
			}
			if (mana[Snow] >= 0) break;
			if (mana[SnowMulticolor] > 0) { // spend multicolor snow mana
				mana[Snow] += 1;
				mana[SnowMulticolor] -= 1;
			} else {
				return false;
			}
		}
		int mana_remaining = 0;
		for (int i = 0; i != ManaEnd; i++) {
			mana_remaining += mana[i];
		}
		mana[Colorless] -= colorless;
		while (mana[Colorless] < 0) {
			bool found = false;
			for (int i = 0; i < 5; i++) { // spend colored mana
				if (mana[colored_mana[i]] > 0) { /** @todo fix me, must predict what color is the best to be spend */
					mana[colored_mana[i]] -= 1;
					mana[Colorless] += 1;
					found = true;
					break;
				}
			}
			if (found) break;
			for (int i = 0; i < 5; i++) { // spend snow mana
				if (mana[colored_mana[i] + 5] > 0) { /** @todo fix me, must predict what color is the best to be spend */
					mana[colored_mana[i] + 5] -= 1;
					mana[Colorless] += 1;
					found = true;
					break;
				}
			}
			if (found) break;
			if (mana[Multicolor] > 0) {
				mana[Multicolor] -= 1;
				mana[Colorless] += 1;
			} else if (mana[SnowMulticolor] > 0) {
				mana[SnowMulticolor] -= 1;
				mana[Colorless] += 1;
			}
		}
	}
	
	vector<string> cost = this->getCost().second;
	for (vector<string>::iterator it = cost.begin(); it != cost.end(); ++it) {
		if (*it == "{T}") {
			if (!this->getCard()->tapped) {
				if (paying) this->getCard()->tapped = true;
			} else {
				return false;
			}
		} else {
			cout << "additional cost ";
			return false;
		}
	}

	if (paying) {
		for (int i = 0; i < sizeof(*pointer) / sizeof(int); i++) {
			(*pointer)[i] = mana[i];
		}
	}
	return true;
}
