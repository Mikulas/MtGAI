//#define NDEBUG // disable asserts

#include <iostream>
#include <string>
#include <time.h>
#include "Database.h"
#include "Game.h"
#include "Card.h"

using namespace std;


int main (int argc, char * const argv[])
{
	srand((unsigned int)time(NULL));
	try {
		Database db = Database();
		Game game = Game();

		//string deck[] = {"Caller of the Hunt", "Caller of the Hunt", "Bone Splinters", "Bone Splinters", "Abandoned Outpost", "Abandoned Outpost", "Abandoned Outpost", "Disenchant", "Disenchant", "Disenchant", "Plains", "Plains", "Island", "Aven Brigadier", "Aven Brigadier", "Aven Brigadier", "Aven Brigadier"};
		//string deck[] = {"Shattering Spree", "Shattering Spree", "Shattering Spree", "Shattering Spree", "Skred", "Skred", "Skred", "Skred", "Mountain", "Mountain", "Mountain", "Mountain", "Mountain"};
		string deck[] = {"Abbey Matron", "Abbey Matron", "Abbey Matron", "Abbey Matron", "Abbey Matron", "Plains", "Plains", "Plains", "Plains", "Plains"};
		for (int p = 0; p < 2; p++) {
			for (int i = 0; i < sizeof(deck) / sizeof(string); i++) {
				Card card = db.get(deck[i]);
				card.owner = &(game.players[p]);
				game.players[p].library.addCard(card);
			}
		}
		game.players[0].library.shuffle();
		game.players[1].library.shuffle();

		game.play();
	} catch(exception &e) {
		cout << endl << endl << "\aSorry, the application has thrown an error!\nPlease send the following message to the author at rullaf@gmail.com:\n";
		cout << "\n\t" << e.what() << endl;
		getchar();
		getchar();
		return 1;
	}

	getchar();
	getchar();
    return 0;
}
