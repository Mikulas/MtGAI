#include "Card.h"

using namespace std;

int Card::id_next = 1;

bool Card::validateSupertype(string supertype)
{
	string supertypes [] = {"basic", "legendary", "ongoing", "snow", "world"};
	for (unsigned int i = 0; i < sizeof(supertypes) / sizeof(string); i++) {
		if (supertypes[i] == supertype)
			return true;
	}
	return false;
}

bool Card::validateType(string type)
{
	string types [] = {"artifact", "creature", "enchantment", "instant", "land", "plane", "planeswalker", "scheme", "sorcery", "tribal", "vanguard"};
	for (unsigned int i = 0; i < sizeof(types) / sizeof(string); i++) {
		if (types[i] == type)
			return true;
	}
	return false;
}

bool Card::validateSubtype(string subtype, vector<string> types)
{
	string artifact [] = {"Contraption", "Equipment", "Fortification"};
	string enchantement [] = {"Aura", "Shrine"};
	string land [] = {"Desert", "Forest", "Island", "Lair", "Locus", "Mine", "Mountain", "Plains", "Power-Plant", "Swamp", "Tower", "Urza’s"};
	string planeswalker [] = {"Ajani", "Bolas", "Chandra", "Elspeth", "Garruk", "Gideon", "Jace", "Koth", "Liliana", "Nissa", "Sarkhan", "Sorin", "Tezzeret", "Venser"};
	string spell [] = {"Arcane", "Trap"};
	string creature [] = {"Advisor", "Ally", "Angel", "Anteater", "Antelope", "Ape", "Archer", "Archon", "Artificer", "Assassin", "Assembly-Worker", "Atog", "Aurochs", "Avatar", "Badger", "Barbarian", "Basilisk", "Bat", "Bear", "Beast", "Beeble", "Berserker", "Bird", "Blinkmoth", "Boar", "Bringer", "Brushwagg", "Camarid", "Camel", "Caribou", "Carrier", "Cat", "Centaur", "Cephalid", "Chimera", "Citizen", "Cleric", "Cockatrice", "Construct", "Coward", "Crab", "Crocodile", "Cyclops", "Dauthi", "Demon", "Deserter", "Devil", "Djinn", "Dragon", "Drake", "Dreadnought", "Drone", "Druid", "Dryad", "Dwarf", "Efreet", "Elder", "Eldrazi", "Elemental", "Elephant", "Elf", "Elk", "Eye", "Faerie", "Ferret", "Fish", "Flagbearer", "Fox", "Frog", "Fungus", "Gargoyle", "Germ", "Giant", "Gnome", "Goat", "Goblin", "Golem", "Gorgon", "Graveborn", "Gremlin", "Griffin", "Hag", "Harpy", "Hellion", "Hippo", "Hippogriff", "Homarid", "Homunculus", "Horror", "Horse", "Hound", "Human", "Hydra", "Hyena", "Illusion", "Imp", "Incarnation", "Insect", "Jellyfish", "Juggernaut", "Kavu", "Kirin", "Kithkin", "Knight", "Kobold", "Kor", "Kraken", "Lammasu", "Leech", "Leviathan", "Lhurgoyf", "Licid", "Lizard", "Manticore", "Masticore", "Mercenary", "Merfolk", "Metathran", "Minion", "Minotaur", "Monger", "Mongoose", "Monk", "Moonfolk", "Mutant", "Myr", "Mystic", "Nautilus", "Nephilim", "Nightmare", "Nightstalker", "Ninja", "Noggle", "Nomad", "Octopus", "Ogre", "Ooze", "Orb", "Orc", "Orgg", "Ouphe", "Ox", "Oyster", "Pegasus", "Pentavite", "Pest", "Phelddagrif", "Phoenix", "Pincher", "Pirate", "Plant", "Prism", "Rabbit", "Rat", "Rebel", "Reflection", "Rhino", "Rigger", "Rogue", "Salamander", "Samurai", "Sand", "Saproling", "Satyr", "Scarecrow", "Scorpion", "Scout", "Serf", "Serpent", "Shade", "Shaman", "Shapeshifter", "Sheep", "Siren", "Skeleton", "Slith", "Sliver", "Slug", "Snake", "Soldier", "Soltari", "Spawn", "Specter", "Spellshaper", "Sphinx", "Spider", "Spike", "Spirit", "Splinter", "Sponge", "Squid", "Squirrel", "Starfish", "Surrakar", "Survivor", "Tetravite", "Thalakos", "Thopter", "Thrull", "Treefolk", "Triskelavite", "Troll", "Turtle", "Unicorn", "Vampire", "Vedalken", "Viashino", "Volver", "Wall", "Warrior", "Weird", "Whale", "Wizard", "Wolf", "Wolverine", "Wombat", "Worm", "Wraith", "Wurm", "Yeti", "Zombie", "Zubera"};

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
}

void Card::addRule(string rule)
{
	cout << "Adding rule " << rule << " to " << this->name << "\n";
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
	if (!Card::validateSupertype(supertype)) {
		cout << "Invalid supertype " << supertype << ", not set\n";
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
	if (!Card::validateType(type)) {
		cout << "Invalid type " << type << ", not set\n";
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
	if (this->types.size() == 0) {
		cout << "Subtype cannot be set to card without any type\n";
	}
	if (!Card::validateSubtype(subtype, this->types)) {
		cout << "Invalid subtype " << subtype << ", not set\n";
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
	for (vector<string>::iterator it = this->supertypes.begin(); it != this->supertypes.end(); ++it) {
		if (*it == supertype) {
			return true;
		}
	}
	return false;
}

bool Card::hasType(string type)
{
	for (vector<string>::iterator it = this->types.begin(); it != this->types.end(); ++it) {
		if (*it == type) {
			return true;
		}
	}
	return false;
}

bool Card::hasSubtype(string subtype)
{
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
	cout << endl;
}
