#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include "Card.h"

using namespace std;

class Database
{
public:
	string * get();
	Card get(string name);
	Card getRandom();
};
