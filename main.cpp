#include <iostream>
#include <string>
#include "Database.h"
#include "Deck.h"

using namespace std;

int main (int argc, char * const argv[])
{
	Database db = Database();
	
	Card a = db.get("Disenchant");
	Card b = db.get("Errand of Duty");

	cout << (a == a ? "a == a" : "a != a") << endl;
	cout << (a == b ? "a == b" : "a != b") << endl;

	Deck deck = Deck();
	deck.addCard(a);
	deck.addCard(a);
	deck.addCard(a);
	//deck.print();
	deck.addCard(b);
	deck.print();
	
	getchar();
	getchar();
    return 0;
}
