#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <regex>
#include <functional>
#include "Callback.h"
#include "Ability.h"
#include "Castable.h"

using namespace std;

// forward declaration
class Player;

class Card : public Callback<Card>, public Castable
{
private:
	static int id_next;
	int id;
	static bool validate(string, string*);

public:
	Player* owner;
	Player* controller;

	static bool validateSupertype(string);
	static bool validateType(string);
	static bool validateSubtype(string, vector<string>);

	vector<string> rules;
	string name;
	string mana_cost;
	int power;
	int toughness;
	int loyalty;
	bool isToken;
	vector<string> supertypes;
	vector<string> types;
	vector<string> subtypes;
	bool tapped;
	bool isUntappable;

	Card(string = "");

	void setPower(int);
	void setToughness(int);
	void addSupertype(string);
	void addType(string);
	void addSubtype(string);
	void addRule(string);
	void makeUnique();

	bool hasSupertype(string);
	bool hasType(string);
	bool hasSubtype(string);

	bool isLimited(); // 4 cards per deck for most cards
	bool isPermanent();
	bool isInstant();
	
	virtual Card* getCard();
	vector<string> getAdditionalCost();
	virtual Castable::Cost getCost();
	void evalute();

	vector<Ability> getAbilities();

	void print();

	bool Card::operator== (Card card) {
		return this->id == card.id;
	}
};
