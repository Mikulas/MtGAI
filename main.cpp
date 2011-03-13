#include <iostream>
#include <string>
#include "Database.h"
#include "Library.h"

using namespace std;

int main (int argc, char * const argv[])
{
	Database db = Database();
	
	Card a = db.get("Disenchant");
	a.addType("sorcery");
	a.addSubtype("Trap");

	Card a2 = db.get("Disenchant");
	Card b = db.get("Errand of Duty");

	cout << (a == a ? "a == a" : "a != a") << endl;
	cout << (a == a2 ? "a == a2" : "a != a2") << endl;
	cout << (a == b ? "a == b" : "a != b") << endl;

	Library lib = Library();
	lib.addCard(a);
	lib.addCard(a);
	lib.addCard(a2);
	//deck.print();
	lib.addCard(b);
	lib.print();
	
	getchar();
	getchar();
    return 0;
}
