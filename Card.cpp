#include "Card.h"
#include "Player.h"

using namespace std;

int Card::id_next = 1;

void toLowerCase(string &str)
{
	for(unsigned int i = 0; i < str.length(); ++i)
	{
		str[i] = tolower(str[i]);
	}
}

bool Card::validateSupertype(string supertype)
{
	toLowerCase(supertype);
	string supertypes [] = {"basic", "legendary", "ongoing", "snow", "world"};
	for (unsigned int i = 0; i < sizeof(supertypes) / sizeof(string); i++) {
		if (supertypes[i] == supertype)
			return true;
	}
	return false;
}

bool Card::validateType(string type)
{
	toLowerCase(type);
	string types [] = {"artifact", "creature", "enchantment", "instant", "land", "plane", "planeswalker", "scheme", "sorcery", "tribal", "vanguard"};
	for (unsigned int i = 0; i < sizeof(types) / sizeof(string); i++) {
		if (types[i] == type)
			return true;
	}
	return false;
}

bool Card::validateSubtype(string subtype, vector<string> types)
{
	toLowerCase(subtype);
	string artifact [] = {"contraption", "equipment", "fortification"};
	string enchantement [] = {"aura", "shrine"};
	string land [] = {"desert", "forest", "island", "lair", "locus", "mine", "mountain", "plains", "power-plant", "swamp", "tower", "urza’s"};
	string planeswalker [] = {"ajani", "bolas", "chandra", "elspeth", "garruk", "gideon", "jace", "koth", "liliana", "nissa", "sarkhan", "sorin", "tezzeret", "venser"};
	string spell [] = {"arcane", "trap"};
	string creature [] = {"advisor", "ally", "angel", "anteater", "antelope", "ape", "archer", "archon", "artificer", "assassin", "assembly-worker", "atog", "aurochs", "avatar", "badger", "barbarian", "basilisk", "bat", "bear", "beast", "beeble", "berserker", "bird", "blinkmoth", "boar", "bringer", "brushwagg", "camarid", "camel", "caribou", "carrier", "cat", "centaur", "cephalid", "chimera", "citizen", "cleric", "cockatrice", "construct", "coward", "crab", "crocodile", "cyclops", "dauthi", "demon", "deserter", "devil", "djinn", "dragon", "drake", "dreadnought", "drone", "druid", "dryad", "dwarf", "efreet", "elder", "eldrazi", "elemental", "elephant", "elf", "elk", "eye", "faerie", "ferret", "fish", "flagbearer", "fox", "frog", "fungus", "gargoyle", "germ", "giant", "gnome", "goat", "goblin", "golem", "gorgon", "graveborn", "gremlin", "griffin", "hag", "harpy", "hellion", "hippo", "hippogriff", "homarid", "homunculus", "horror", "horse", "hound", "human", "hydra", "hyena", "illusion", "imp", "incarnation", "insect", "jellyfish", "juggernaut", "kavu", "kirin", "kithkin", "knight", "kobold", "kor", "kraken", "lammasu", "leech", "leviathan", "lhurgoyf", "licid", "lizard", "manticore", "masticore", "mercenary", "merfolk", "metathran", "minion", "minotaur", "monger", "mongoose", "monk", "moonfolk", "mutant", "myr", "mystic", "nautilus", "nephilim", "nightmare", "nightstalker", "ninja", "noggle", "nomad", "octopus", "ogre", "ooze", "orb", "orc", "orgg", "ouphe", "ox", "oyster", "pegasus", "pentavite", "pest", "phelddagrif", "phoenix", "pincher", "pirate", "plant", "prism", "rabbit", "rat", "rebel", "reflection", "rhino", "rigger", "rogue", "salamander", "samurai", "sand", "saproling", "satyr", "scarecrow", "scorpion", "scout", "serf", "serpent", "shade", "shaman", "shapeshifter", "sheep", "siren", "skeleton", "slith", "sliver", "slug", "snake", "soldier", "soltari", "spawn", "specter", "spellshaper", "sphinx", "spider", "spike", "spirit", "splinter", "sponge", "squid", "squirrel", "starfish", "surrakar", "survivor", "tetravite", "thalakos", "thopter", "thrull", "treefolk", "triskelavite", "troll", "turtle", "unicorn", "vampire", "vedalken", "viashino", "volver", "wall", "warrior", "weird", "whale", "wizard", "wolf", "wolverine", "wombat", "worm", "wraith", "wurm", "yeti", "zombie", "zubera"};

	for (vector<string>::iterator it = types.begin(); it != types.end(); ++it) {
		string type = *it;
		validateType(type);
		if (type == "artifact") for (unsigned int i = 0; i < sizeof(artifact) / sizeof(string); i++) {if (artifact[i] == subtype) return true;};
		if (type == "enchantement") for (unsigned int i = 0; i < sizeof(enchantement) / sizeof(string); i++) {if (enchantement[i] == subtype) return true;};
		if (type == "land") for (unsigned int i = 0; i < sizeof(land) / sizeof(string); i++) {if (land[i] == subtype) return true;};
		if (type == "planeswalker") for (unsigned int i = 0; i < sizeof(planeswalker) / sizeof(string); i++) {if (planeswalker[i] == subtype) return true;};
		if (type == "instant" || type == "sorcery") for (unsigned int i = 0; i < sizeof(spell) / sizeof(string); i++) {if (spell[i] == subtype) return true;};
		if (type == "creature") for (unsigned int i = 0; i < sizeof(creature) / sizeof(string); i++) {if (creature[i] == subtype) return true;};
	}
	return false;
}

Card::Card(string name)
{
	this->id = Card::id_next;
	Card::id_next++;
	this->name = name;
	this->power = 0;
	this->toughness = 0;
	this->loyalty = 0;
	this->tapped = false;
	this->isUntappable = true;
}

void Card::addRule(string rule)
{
	tr1::regex rg_enters = tr1::regex(this->name + " enters the battlefield ([^.]+).");
	tr1::cmatch res;
	if (regex_match(rule.c_str(), res, rg_enters) && res[1] == "tapped") {
		this->registerCallback("enterBattlefield", [this](Card* card) {
			cout << this->name << " enters the battlefield tapped" << endl;
			this->tapped = true;
		});
	}
	this->rules.push_back(rule);
}

void Card::setPower(int power)
{
	this->power = power;
}

void Card::setToughness(int toughness)
{
	this->toughness = toughness;
}

void Card::addSupertype(string supertype)
{
	toLowerCase(supertype);
	if (!Card::validateSupertype(supertype)) {
		throw exception("Invalid supertype");
	}
	bool alreadySet = false;
	for (vector<string>::iterator it = this->supertypes.begin(); it != this->supertypes.end(); ++it) {
		if (*it == supertype) {
			alreadySet = true;
			break;
		}
	}
	if (!alreadySet) {
		this->supertypes.push_back(supertype);
	}
}

void Card::addType(string type)
{
	toLowerCase(type);
	if (!Card::validateType(type)) {
		throw exception("Invalid type");
	}
	bool alreadySet = false;
	for (vector<string>::iterator it = this->types.begin(); it != this->types.end(); ++it) {
		if (*it == type) {
			alreadySet = true;
			break;
		}
	}
	if (!alreadySet) {
		this->types.push_back(type);
	}
}

void Card::addSubtype(string subtype)
{
	toLowerCase(subtype);
	if (this->types.size() == 0) {
		throw exception("Subtype cannot be set to card without any type");
	}
	if (!Card::validateSubtype(subtype, this->types)) {
		throw exception("Invalid suptype");
	}
	bool alreadySet = false;
	for (vector<string>::iterator it = this->subtypes.begin(); it != this->subtypes.end(); ++it) {
		if (*it == subtype) {
			alreadySet = true;
			break;
		}
	}
	if (!alreadySet) {
		this->subtypes.push_back(subtype);
	}
}

bool Card::hasSupertype(string supertype)
{
	toLowerCase(supertype);
	for (vector<string>::iterator it = this->supertypes.begin(); it != this->supertypes.end(); ++it) {
		if (*it == supertype) {
			return true;
		}
	}
	return false;
}

bool Card::hasType(string type)
{
	toLowerCase(type);
	for (vector<string>::iterator it = this->types.begin(); it != this->types.end(); ++it) {
		if (*it == type) {
			return true;
		}
	}
	return false;
}

bool Card::hasSubtype(string subtype)
{
	toLowerCase(subtype);
	for (vector<string>::iterator it = this->subtypes.begin(); it != this->subtypes.end(); ++it) {
		if (*it == subtype) {
			return true;
		}
	}
	return false;
}

bool Card::isPermanent()
{
	// return true if is in proper zone;
	return true; // todo implement
}

bool Card::isLimited()
{
	return !this->hasSupertype("basic");
}

void Card::print()
{
	cout << "name: " << this->name << endl;
	cout << "\tcost: " << this->mana_cost << endl;
	cout << "\tloyalty: " << this->loyalty << endl;
	cout << "\tpower: " << this->power << endl;
	cout << "\ttoughness: " << this->toughness << endl;

	cout << "\tsupertypes: ";
	for (vector<string>::iterator it = this->supertypes.begin(); it != this->supertypes.end(); ++it) {
		cout << *it << ", ";
	}
	cout << endl << "\ttypes: ";
	for (vector<string>::iterator it = this->types.begin(); it != this->types.end(); ++it) {
		cout << *it << ", ";
	}
	cout << endl << "\tsubtypes: ";
	for (vector<string>::iterator it = this->subtypes.begin(); it != this->subtypes.end(); ++it) {
		cout << *it << ", ";
	}
	cout << endl << "\trules: ";
	for (vector<string>::iterator it = this->rules.begin(); it != this->rules.end(); ++it) {
		cout << *it << ", ";
	}
	cout << endl;
}

void Card::makeUnique()
{
	this->id = Card::id_next;
	Card::id_next++;
}

bool Card::isInstant()
{
	bool hasFlash = false;
	for (vector<string>::iterator it = this->rules.begin(); it != this->rules.end(); ++it) {
		if (*it == "Flash") {
			hasFlash = true;
			break;
		}
	}
	return hasFlash || this->hasType("instant");
}

void Card::evalute()
{

}

vector<pair<string, string>> Card::permanentAbilities()
{
	vector<pair<string, string>> abilities;
	tr1::regex ability = tr1::regex("([^:]+): ([^.]+).");
	tr1::cmatch res;
	for (vector<string>::iterator it = this->rules.begin(); it != this->rules.end(); ++it) {
		if (tr1::regex_match((*it).c_str(), res, ability)) {
			abilities.push_back(make_pair(res[1], res[2]));
		}
	}
	for (vector<string>::iterator it = this->subtypes.begin(); it != this->subtypes.end(); ++it) { // basic land handler
		if (*it == "forrest") {
			abilities.push_back(make_pair("{T}", "Add {G} to your mana pool"));
		} else if (*it == "island") {
			abilities.push_back(make_pair("{T}", "Add {U} to your mana pool"));
		} else if (*it == "mountain") {
			abilities.push_back(make_pair("{T}", "Add {R} to your mana pool"));
		} else if (*it == "plains") {
			abilities.push_back(make_pair("{T}", "Add {W} to your mana pool"));
		} else if (*it == "swamp") {
			abilities.push_back(make_pair("{T}", "Add {B} to your mana pool"));
		}
	}

	return abilities;
}

vector<string> Card::getAdditionalCost()
{
	vector<string> cost;

	tr1::regex rg_cost = tr1::regex("As an additional cost to cast " + this->name + ", ([^.]*).");
	tr1::cmatch res;
	for (vector<string>::iterator it = this->rules.begin(); it != this->rules.end(); ++it) {
		if (tr1::regex_match((*it).c_str(), res, rg_cost)) {
			cost.push_back(res[1]);
		}
	}
	return cost;
}

void Card::printCost()
{
	vector<string> cost = this->getAdditionalCost();
	cout << this->mana_cost;
	for (vector<string>::iterator it = cost.begin(); it != cost.end(); ++it) {
		cout << ", " << *it;
	}
}

bool Card::isCastable(Player* caster)
{
	tr1::regex rg_mana("(\\d+)?([GURWBS]|\\{[GURWB]{2}\\}|\\{(X|Y)\\})*");
	tr1::cmatch res;
	bool implementedWarning = false;
	if (tr1::regex_match(this->mana_cost.c_str(), res, rg_mana)) {
		tr1::regex rg_color("[GURWBS]|\\{GURWB\\}");
		tr1::sregex_token_iterator end;
		string match(res[2]);
		int mana[12] = {0};
		mana[Colorless] = atoi(string(res[1]).c_str());
		for (tr1::sregex_token_iterator it(match.begin(), match.end(), rg_color); it != end; it++) {
			if (*it == "G") mana[Forest]++;
			else if (*it == "U") mana[Island]++;
			else if (*it == "R") mana[Mountain]++;
			else if (*it == "W") mana[Plains]++;
			else if (*it == "B") mana[Swamp]++;
			else if (*it == "S") mana[Snow]++;
			else {cout << "choice cost "; implementedWarning = true;}
		}
		int sum = 0;
		for (int i = Forest; i != Snow; i++) {
			sum += mana[i];
			if (i == Colorless || i == SnowColorless)
				continue;
			if (mana[i] > caster->mana[i])
				return false;
		}
		// do we have enought mana to pay colorless from the resources left?
		if (caster->getManaSum() < sum) {
			return false;
		}
	}
		
	vector<string> cost = this->getAdditionalCost();
	for (vector<string>::iterator it = cost.begin(); it != cost.end(); ++it) {
		if (implementedWarning) cout << "and ";
		cout << "additional cost ";
		implementedWarning = true;
		// cout << " X ", *it;
	}
	if (implementedWarning) cout << "are not implemented yet" << endl;
	return true;
}

void Card::payCost(Player* caster)
{
	if (!this->isCastable(caster)) {
		throw exception("The card is not castable, cannot pay cost");
	}
	tr1::regex rg_mana("(\\d+)?([GURWBS]|\\{[GURWB]{2}\\}|\\{(X|Y)\\})*");
	tr1::cmatch res;
	/** @todo implement */
	bool implementedWarning = false;
	if (tr1::regex_match(this->mana_cost.c_str(), res, rg_mana)) {
		int colorless = atoi(string(res[1]).c_str());
		
		// spend as much mana as possible from colorless and then spending the most frequent color in the pool
		int highest = Forest;
		while (caster->mana[Colorless] < colorless) {
			for (int i = Forest; i != Snow; i++) 
				if (caster->mana[highest] > caster->mana[i]) highest = i;
			caster->setMana((Mana) highest, -1);
		}
		caster->setMana(Colorless, -colorless);
		
		tr1::regex rg_color("[GURWBS]|\\{GURWB\\}");
		tr1::sregex_token_iterator end;
		string match(res[2]);
		int mana[12] = {0};
		for (tr1::sregex_token_iterator it(match.begin(), match.end(), rg_color); it != end; it++) {
			if (*it == "G") mana[Forest]++;
			else if (*it == "U") mana[Island]++;
			else if (*it == "R") mana[Mountain]++;
			else if (*it == "W") mana[Plains]++;
			else if (*it == "B") mana[Swamp]++;
			else if (*it == "S") mana[Snow]++;
			else cout << "choice cost "; implementedWarning++;
		}
		for (int i = Forest; i != Snow; i++) {
			if (mana[i] > caster->mana[i]) {
				return;
			}
		}
	}
		
	vector<string> cost = this->getAdditionalCost();
	for (vector<string>::iterator it = cost.begin(); it != cost.end(); ++it) {
		if (implementedWarning) cout << "and ";
		cout << "additional cost "; implementedWarning++;
		// cout << " X ", *it;
	}
	if (implementedWarning) cout << "are not implemented yet" << endl;
	return;
}
