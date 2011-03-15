#include "Game.h"

Game::Game()
{
	this->players[0].stack = this->players[1].stack = &this->stack;
	this->active = 0; // defaults to first player
	this->priority = -1; // defaults to none
}

Player* Game::getPriorityPlayer()
{
	if (this->priority == -1) {
		throw exception("No player has priority");
	}
	return &this->players[this->priority];
}


Player* Game::getActivePlayer()
{
	return &this->players[this->active];
}

Player* Game::getInactivePlayer()
{
	return &this->players[this->active == 0 ? 1 : 0];
}

void Game::registerCallbackPlayers(string name, function<void()> callback)
{
	this->players[0].registerCallback(name, callback);
	this->players[1].registerCallback(name, callback);
}

void Game::switchPriority()
{
	if (this->priority == -1) {
		throw exception("No player has priority");
	}
	this->priority = this->priority == 0 ? 1 : 0;
	this->getPriorityPlayer()->callback("receivedPriority");
}

bool Game::playersPassed()
{
	return this->players[0].passed && this->players[1].passed;
}

void Game::playByPriority(bool mainPhase)
{
	this->players[0].passed = this->players[1].passed = false;
	this->priority = this->active;
	this->getPriorityPlayer()->callback("receivedPriority");
	while (!this->playersPassed()) {
		if (this->active == this->priority) cout << "priority is on ACTIVE player: ";
		else cout << "priority is on inactive player: ";
		
		this->getPriorityPlayer()->play(this->priority == this->active && this->stack.isEmpty() && mainPhase);
		if (!this->stack.isEmpty() || this->getPriorityPlayer()->passed) { // if land was not played
			this->switchPriority();
		}
		if (!this->stack.isEmpty() && this->playersPassed()) {
			this->stack.execute();
			this->players[0].passed = this->players[1].passed = false;
			this->priority = this->active;
		}
	}
	this->priority = this->active;
}

void Game::end(int winner)
{
	cout << "Player #" << winner + 1 << " won" << endl;
	getchar();
	getchar();
	exit(winner);
}

void Game::turn()
{
	Player *active = this->getActivePlayer();
	Player *opponent = this->getInactivePlayer();

	cout << "### beginning" << endl;
	//- untap
		//phase in and out simultaneously, no stack
		//optional untap, no stack
	active->battlefield.foreach([&](Card *card) {
		card->tapped = card->isUntappable;
	});
		//begin upkeep trigger
	this->callback("beginUpkeep");
		//untap trigger
	this->callback("untap");
		//active player priority
	cout << "### beginning - draw" << endl;
	this->playByPriority(false);
		//active player draws a card
	if (active->canDraw)
		active->draw();
		//begin draw trigger
	cout << "### beginning - upkeep" << endl;
	this->callback("draw");
		//active player priority
	this->playByPriority(false);
	//
	cout << "### precombat main" << endl;
	//	begin main phase trigger
	//	active player priority
	//	active player can play land, artifact, creature, enchantement, planeswalker, sorcery
	//	lands do not enter stack
	this->playByPriority(true);
	//
	cout << "### combat" << endl;
	//- beginning of combat
	//	
	//- declare attackers
	//- declare blockers
	//- combat damage
	//- end of combat
	//
	cout << "### postcombat main" << endl;
		//active player priority
	this->playByPriority(true);
	//
	cout << "### end" << endl;
	this->callback("cleanup");

}

void Game::play()
{
	bool playing = true;

	this->registerCallbackPlayers("receivedPriority", [&](){
		Player* player = this->getPriorityPlayer();
		if (player->library.cards.size() == 0) {
			cout << "player lost - no more cards in the deck" << endl;
			this->end(this->active == 0 ? 1 : 0);
		}
		if (player->life <= 0) {
			cout << "player lost - life depleted" << endl;
			this->end(this->active == 0 ? 1 : 0);
		}
		if (player->poison >= 10) {
			cout << "player lost - too much poison counters" << endl;
			this->end(this->active == 0 ? 1 : 0);
		}
	});
	this->registerCallback("cleanup", [&](){
		if (this->getActivePlayer()->hand.cards.size() > 7) { // only active player has to discard
			cout << "player has more than 7 cards in hand" << endl;
			this->getActivePlayer()->hand.discard(this->getActivePlayer()->hand.cards.size() - 7);
		}
	});


	for (int i = 0; i < sizeof(this->players) / sizeof(Player); i++) {
		for (int c = 0; c < 7; c++)
			this->players[i].draw();
	}

	while (true) {
		cout << "________________\nTurn of player " << this->active + 1 << endl;
		this->turn();
		this->active = this->active == 0 ? 1 : 0;
	}
}
