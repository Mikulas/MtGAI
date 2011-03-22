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
		/** @todo fixme */
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
	tr1::regex rg_enters(this->name + " enters the battlefield ([^.]+).");
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
	/** @todo "A permanent is a card or token on the battlefield." Does this work well? */
	return !this->hasType("instant") && !this->hasType("sorcery");
}

bool Card::isLimited()
{
	for (vector<string>::iterator rule = this->rules.begin(); rule != this->rules.end(); ++rule) {
		if (*rule == string("A deck can have any number of cards named ") + this->name)
			return false;
	}

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
	for (vector<string>::iterator rule = this->rules.begin(); rule != this->rules.end(); ++rule) {
		if (*rule == "Flash") {
			hasFlash = true;
			break;
		}
	}
	return hasFlash || this->hasType("instant");
}

void Card::evalute()
{

}

vector<Ability> Card::getAbilities()
{
	vector<Ability> abilities;
	tr1::regex ability("([^:]+): ([^.]+).");
	tr1::cmatch res;
	for (vector<string>::iterator rule = this->rules.begin(); rule != this->rules.end(); ++rule) {
		if (tr1::regex_match(rule->c_str(), res, ability))
			abilities.push_back(Ability(this, res[1], res[2]));
	}
	for (vector<string>::iterator subtype = this->subtypes.begin(); subtype != this->subtypes.end(); ++subtype) { // basic land handler
		string effect = "";
		if (*subtype == "forest") {
			effect = "Add {G} to your mana pool";
		} else if (*subtype == "island") {
			effect = "Add {U} to your mana pool";
		} else if (*subtype == "mountain") {
			effect = "Add {R} to your mana pool";
		} else if (*subtype == "plains") {
			effect = "Add {W} to your mana pool";
		} else if (*subtype == "swamp") {
			effect = "Add {B} to your mana pool";
		}
		if (effect != "") {
			abilities.push_back(Ability(this, "{T}", effect));
		}
	}

	return abilities;
}

vector<string> Card::getAdditionalCost()
{
	vector<string> cost;

	tr1::regex rg_cost("As an additional cost to cast " + this->name + ", ([^.]*).");
	tr1::cmatch res;
	for (vector<string>::iterator rule = this->rules.begin(); rule != this->rules.end(); ++rule) {
		if (tr1::regex_match(rule->c_str(), res, rg_cost))
			cost.push_back(res[1]);
	}
	return cost;
}

Castable::Cost Card::getCost()
{
	return make_pair(this->mana_cost, this->getAdditionalCost());
}

Card* Card::getCard()
{
	return this;
}
