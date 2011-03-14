#include <iostream>

#include <string>
#include <time.h>
#include "Database.h"
#include "Game.h"

using namespace std;

int main (int argc, char * const argv[])
{
	srand((unsigned int)time(NULL));

	//Database::buildCache();
	Database db = Database();
	
	Game game = Game();
	string deck[] = {"Abandoned Outpost", "Disenchant", "Plains", "Plains", "Island"};
	for (int i = 0; i < sizeof(deck) / sizeof(string); i++) {
		game.players[0].library.addCard(db.get(deck[i]));
	}
	
	game.players[0].print();
	game.players[0].library.shuffle();
	game.players[0].print();
	game.players[0].draw();
	game.players[0].print();
	
	getchar();
	getchar();
    return 0;
}
