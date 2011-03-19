#include "Castable.h"
#include "Player.h"

bool Castable::isCastable(Player* player)
{
	return true;
	/*tr1::regex rg_cost = tr1::regex("Add (({(1|G|B|R|W|B)})+|one mana of any color) to your mana pool");
	tr1::cmatch res;
	
	vector<string> cost = this->getCost();
	for (vector<string>::iterator it = cost.begin(); it != cost.end(); ++it) {
		if (tr1::regex_match((*it).c_str(), res, rg_cost) {
			if (res[1] == "one mana of any color")
		}
	}*/
}
