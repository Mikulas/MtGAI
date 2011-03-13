#include <iostream>

#include <string>
#include "Database.h"
#include "Player.h"

using namespace std;

int main (int argc, char * const argv[])
{
	Database db = Database();
	Player p1 = Player();

	p1.library.addCard(db.get("Disenchant"));
	p1.library.addCard(db.get("Disenchant"));
	p1.library.addCard(db.get("Disenchant"));
	p1.library.addCard(db.get("Plains"));
	p1.library.addCard(db.get("Plains"));
	p1.library.addCard(db.get("Plains"));
	p1.library.addCard(db.get("Plains"));
	
	p1.print();
	p1.draw();
	p1.print();
	
	getchar();
	getchar();
    return 0;
}
