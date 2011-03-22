#include "Database.h"

using namespace std;

void findAndReplace(string &tInput, string tFind, string tReplace) {
	size_t uPos = 0;
	size_t uFindLen = tFind.length();
	size_t uReplaceLen = tReplace.length();	
	if (uFindLen == 0) {
		return;
	}
	
	while ((uPos = tInput.find(tFind, uPos)) != string::npos) {
		tInput.replace(uPos, uFindLen, tReplace);
		uPos += uReplaceLen;
	}
}

vector<Card> Database::cache;

void Database::buildCache()
{
	ifstream data;
	data.open("C:\\Users\\Mikulas\\Documents\\Visual Studio 2010\\Projects\\MtGAI\\data\\cards.xml");
	string input;
	tr1::regex rg_card(" <card>");
	tr1::regex rg_node("[ \t]*<([^ ]+)([^>]*)>(.*?)</([^>]+)>");
	tr1::cmatch res;

	cout << "building card database cache...\n";

	if (!data.is_open()) {
		throw exception("Database file not found");
	}
	
	Card card = Card();
	int size = 145868;
	int line = 0;
	while (!data.eof()) {
		line ++;
		cout << "\rline " << line << " out of " << size << " [" << (double) line / (double) size << "%]       ";
		getline(data, input);

		if (regex_match(input.c_str(), res, rg_card)) {
			Database::cache.push_back(card);
			card = Card();
			continue;
		}

		if (regex_match(input.c_str(), res, rg_node)) {
			string node = res[1].str();
			string value = res[3].str();

			if (node == "name") card.name = value;
			if (node == "pow") card.power = atoi(value.c_str());
			if (node == "tgh") card.toughness = atoi(value.c_str());
			if (node == "rule") card.addRule(value);
			if (node == "type" && Card::validateSupertype(value)) card.addSupertype(value);
			if (node == "type" && Card::validateType(value)) card.addType(value);
			if (node == "type" && Card::validateSubtype(value, card.types)) card.addSubtype(value);
			if (node == "cost") card.mana_cost = value;
		}
	}
	data.close();
	cout << "\r                                         \rdone\n";
}

bool Database::isCached(string name)
{
	for (vector<Card>::iterator it = Database::cache.begin(); it != Database::cache.end(); ++it) {
		if (it->name == name) {
			return true;
		}
	}
	return false;
}

Card Database::get(string name)
{
	bool cached = false;
	vector<Card>::iterator it = Database::cache.begin();
	for (; it != Database::cache.end(); ++it) {
		if (it->name == name) {
			cached = true;
			break;
		}
	}
	if (!cached) {
		ifstream data;
		data.open("C:\\Users\\Mikulas\\Documents\\Visual Studio 2010\\Projects\\MtGAI\\data\\cards.xml");
		//data.open("X:\\Projects\\MtGAI\\data\\cards.xml");
		string input;
		tr1::regex rg_card(string("[ \t]*<name>") + name + string("</name>"));
		tr1::regex rg_node("[ \t]*<([^ ]+)([^>]*)>(.*?)</([^>]+)>");
		tr1::regex rg_card_end("[ \t]*</card>");
		tr1::cmatch res;

		if (!data.is_open()) {
			throw exception("Database file not found");
		}
		
		Card card = Card();
		bool found = false;

		while (!data.eof()) {
			getline(data, input);

			if (regex_match(input.c_str(), res, rg_card)) {
				found = true;
			}

			if (found && regex_match(input.c_str(), res, rg_node)) {
				string node = res[1].str();
				string value = res[3].str();

				if (node == "name") card.name = value;
				if (node == "pow") card.power = atoi(value.c_str());
				if (node == "tgh") card.toughness = atoi(value.c_str());
				if (node == "rule") card.addRule(value);
				if (node == "type" && Card::validateSupertype(value)) card.addSupertype(value);
				if (node == "type" && Card::validateType(value)) card.addType(value);
				if (node == "type" && Card::validateSubtype(value, card.types)) card.addSubtype(value);
				if (node == "cost") card.mana_cost = value;
			}

			if (found && regex_match(input.c_str(), res, rg_card_end)) {
				break;
			}
		}
		if (!found) {
			throw exception("Card does not exist");
		}
		data.close();
		Database::cache.push_back(card);
		card.makeUnique();
		return card;
	}

	Card card = *it;
	card.makeUnique();
	return card;
}
