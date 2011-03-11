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

string * Database::get()
{
	ifstream data;
	data.open("../../data/cards.xml");
	string input;
	bool isCard = false;
	int pos = -1;
	int count = 0;
	while (!data.eof()) {
		getline(data, input);
		if (input.find("<card>") != string::npos) {
			isCard = true;
			continue;
		}
		if (isCard && (pos = input.find("<name>")) != string::npos) {
			count++;
			input = input.substr(pos + 6, input.length() - pos - 6 - 7);
			
			findAndReplace(input, "&apos;", "'");
			findAndReplace(input, "&quot;", "\"");
			cout << input << "\n";
			isCard = false;
		}
	}
	cout << "\ntotal card count = " << count << "\n";
	data.close();

	string ret = string("RETURN");
	return &ret;
}

Card Database::get(string name)
{
	ifstream data;
	data.open("C:\\Users\\Mikulas\\Documents\\Visual Studio 2010\\Projects\\MtGAI\\data\\cards.xml");
	string input;
	bool cardFound = false;
	
	tr1::regex rx("[ \t]*<name>(.*?)</name>");
	string row = string("<name>") + name + string("</name>");
	Card card = Card(name);
	
	if (!data.is_open()) {
		cout << "file not found\n";
		return Card("unknown card");
	}

	//typedef match_results<const char*> cmatch;

	while (!data.eof()) {
		getline(data, input);
		tr1::cmatch res;

		if (regex_match(input.c_str(), res, rx)) {
			cout << res[1] << "\n";
		}

		if (input.find(row) != string::npos) {
			findAndReplace(name, "&apos;", "'");
			findAndReplace(name, "&quot;", "\"");
			cardFound = true;
		}
		if (cardFound && (input.find("<rule ") != string::npos || input.find("<rule>") != string::npos)) {
			card.addRule(input);
		}
		if (cardFound && input.find("</card>") != string::npos) {
			break;
		}
	}
	data.close();
	
	return card;
}

Card Database::getRandom()
{
	return Card("random");
}
