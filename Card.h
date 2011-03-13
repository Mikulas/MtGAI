#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Card
{
private:
	static int id_next;
	int id;
	static bool validate(string, string*);
	static bool validateSupertype(string);
	static bool validateType(string);
	static bool validateSubtype(string, vector<string>);

public:
	vector<string> rules;
	string name;
	string mana_cost;
	vector<string> color;
	int power;
	int toughness;
	int loyalty;
	vector<string> supertypes; // basic, legendary, ongoing, snow, and world
	vector<string> types; // artifact, creature, enchantement, instant, land, plane, planeswalker, scheme, sorcery, tribal, vanguard
	vector<string> subtypes;
		/* rules section 204.3k for creatures
		artifact - Contraption, Equipment, Fortification
		enchantement - Aura, Shrine
		land -  Desert, Forest, Island, Lair, Locus, Mine, Mountain, Plains, Power-Plant, Swamp, 
	Tower, Urza’s
			Of that list, Forest, Island, Mountain, Plains, and Swamp are the basic land types
		planeswalker - Ajani, Bolas, Chandra, Elspeth, Garruk, Gideon, Jace, Koth, 
	Liliana, Nissa, Sarkhan, Sorin, Tezzeret, Venser
		instant and sorcery - Arcane, Trap
		planes are 204.3m */
	
	Card(string);
	bool isLimited(); // 4 cards per deck for most cards
	void setPower(int);
	void setToughness(int);
	void addSupertype(string);
	void addType(string);
	void addSubtype(string);
	void addRule(string);
	

	bool Card::operator== (Card card) {
		return this->id == card.id;
	}
};
