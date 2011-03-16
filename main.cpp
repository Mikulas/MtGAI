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

	string deck[] = {"Caller of the Hunt", "Caller of the Hunt", "Bone Splinters", "Bone Splinters", "Abandoned Outpost", "Abandoned Outpost", "Abandoned Outpost", "Disenchant", "Disenchant", "Disenchant", "Plains", "Plains", "Island", "Aven Brigadier", "Aven Brigadier", "Aven Brigadier", "Aven Brigadier"};
	for (int i = 0; i < sizeof(deck) / sizeof(string); i++) {
		game.players[0].library.addCard(db.get(deck[i]));
		game.players[1].library.addCard(db.get(deck[i]));
	}
	game.players[0].library.shuffle();
	game.players[1].library.shuffle();

	game.play();

	getchar();
	getchar();
    return 0;
}
