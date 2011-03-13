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
	
	tr1::regex rg_name("[ \t]*<name>(.*?)</name>");
	tr1::regex rg_rule("[ \t]*<rule([^>]*)>(.*?)</rule>");
	Card card = Card(name);
	
	if (!data.is_open()) {
		cout << "file not found\n";
		return Card("unknown card");
	}
	
	while (!data.eof()) {
		getline(data, input);
		tr1::cmatch res;

		if (regex_match(input.c_str(), res, rg_name)) {
			//cout << res[1] << "\n";
			//findAndReplace(res[1], "&apos;", "'");
			//findAndReplace(res[1], "&quot;", "\"");
			if (res[1] == name) {
				cardFound = true;
				continue;
			}
		}
		if (cardFound && regex_match(input.c_str(), res, rg_rule)) {
			card.addRule(res[2]);
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
