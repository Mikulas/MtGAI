#include "Game.h"

Game::Game()
{
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

void Game::playByPriority()
{
	this->players[0].passed = this->players[1].passed = false;
	this->priority = this->active;
	this->getPriorityPlayer()->callback("receivedPriority");
	while (!this->playersPassed()) {
		this->getPriorityPlayer()->play();
		if (this->getPriorityPlayer()->passed) {
			this->switchPriority();
		}
		if (this->playersPassed() && !this->stack.isEmpty()) {
			this->stack.execute();
			this->players[0].passed = this->players[1].passed = false;
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

	//beginning
	//- untap
		//phase in and out simultaneously, no stack
		//optional untap, no stack
	active->battlefield.foreach([&](Card *card) {
		card->tapped = card->isUntappable;
	});
		//no priority
	//- upkeep
		//begin upkeep trigger
	this->callback("beginUpkeep");
		//untap trigger
	this->callback("untap");
		//active player priority
	this->playByPriority();
		
	//- draw
		//active player draws a card
	if (active->canDraw)
		active->draw();
		//begin draw trigger
	
	this->callback("draw");
		//active player priority
	this->playByPriority();
	//
	//precombat main
	//	begin main phase trigger
	//	active player priority
	//	active player can play land, artifact, creature, enchantement, planeswalker, sorcery
	//	lands do not enter stack
	//
	//combat
	//- beginning of combat
	//	
	//- declare attackers
	//- declare blockers
	//- combat damage
	//- end of combat
	//
	//postcombat main
		//active player priority
	this->playByPriority();
	//
	//ending
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
		if (player->poisson >= 10) {
			cout << "player lost - too much poisson counters" << endl;
			this->end(this->active == 0 ? 1 : 0);
		}
	});
	this->registerCallback("cleanup", [&](){
		if (this->getActivePlayer()->hand.cards.size() > 7) { // only active player has to discard
			cout << "player has more than 7 cards in hand" << endl;
			this->getActivePlayer()->hand.discard(this->getActivePlayer()->hand.cards.size() - 7);
		}
	});

	while (true) {
		cout << "Turn of player " << this->active + 1 << endl;
		this->turn();
		this->active = this->active == 0 ? 1 : 0;
	}
}
