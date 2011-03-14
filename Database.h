#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include "Card.h"

using namespace std;

class Database
{
private:
	static vector<Card> cache;
	static bool isCached(string);

public:
	static void buildCache();

	Card get(string);
};
