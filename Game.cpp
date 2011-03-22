#include "Game.h"

Game::Game()
{
	this->players[0].id = 0;
	this->players[1].id = 1;
	this->players[0].game = this->players[1].game = this;
	this->priority = this->active = 0; // defaults to first player
}

Player* Game::getPriorityPlayer()
{
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

void Game::switchPriority()
{
	this->priority = this->priority == 0 ? 1 : 0;
	this->getPriorityPlayer()->callback("receivedPriority", this->getPriorityPlayer());
}

bool Game::playersPassed()
{
	return this->players[0].passed && this->players[1].passed;
}

void Game::playByPriority(bool mainPhase)
{
	this->players[0].passed = this->players[1].passed = false;
	this->priority = this->active;
	this->getPriorityPlayer()->callback("receivedPriority", this->getPriorityPlayer());
	while (!this->playersPassed()) {
		if (this->active == this->priority) cout << "* priority is on active player: ";
		else cout << "* priority is on inactive player: ";
		
		bool sorceryOnly = this->priority == this->active && this->stack.isEmpty() && mainPhase;
		this->getPriorityPlayer()->play(sorceryOnly);
		// TODO handle mana abilities when stack is not empty - now it switches priority
		if (!this->stack.isEmpty() || this->getPriorityPlayer()->passed) { // if land was not played
			this->switchPriority();
		}
		if (!this->stack.isEmpty() && this->playersPassed()) {
			this->stack.execute();
			this->players[0].passed = this->players[1].passed = false;
			this->priority = this->active;
		}
	}
}

void Game::end(int winner)
{
	cout << "Player #" << winner + 1 << " won" << endl;
	getchar();
	getchar();
	exit(winner);
}

void Game::turn(int turn_number)
{
	Player *active = this->getActivePlayer();
	Player *opponent = this->getInactivePlayer();

	cout << "### beginning" << endl;
	//- untap
		//phase in and out simultaneously, no stack
	active->battlefield.foreach([&](Card *card) {
		card->callback("phase", card);
	});
		//optional untap, no stack
	active->battlefield.foreach([&](Card *card) {
		card->tapped = card->isUntappable; // TODO untapping does not work properly
	});
		//begin upkeep trigger
	this->callback("beginUpkeep", this);
		//untap trigger
	this->callback("untap", this);
		//active player priority
	cout << "### beginning - draw" << endl;
	this->playByPriority(false);
	this->callback("nextPhase", this);
		//active player draws a card
	if (turn_number != 0 && active->canDraw)
		active->draw();
		//begin draw trigger
	cout << "### beginning - upkeep" << endl;
	this->callback("draw", this);
		//active player priority
	this->playByPriority(false);
	this->callback("nextPhase", this);
	//
	cout << "### precombat main" << endl;
	//	begin main phase trigger
	//	active player priority
	//	active player can play land, artifact, creature, enchantement, planeswalker, sorcery
	//	lands do not enter stack
	this->playByPriority(true);
	this->callback("nextPhase", this);
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
	callback("nextPhase", this);
	//
	cout << "### end" << endl;
	this->callback("nextPhase", this);
	this->callback("cleanup", this);
}

void Game::play()
{
	bool playing = true;
	for (int i = 0; i < sizeof(this->players) / sizeof(Player); i++) {
		this->players[i].registerCallback("receivedPriority", [&](Player* player){
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
	}
	this->registerCallback("cleanup", [&](Game* game) {
		if (this->getActivePlayer()->hand.cards.size() > 7) { // only active player has to discard
			cout << "player has more than 7 cards in hand" << endl;
			this->getActivePlayer()->hand.discard(this->getActivePlayer()->hand.cards.size() - 7);
		}
		this->getActivePlayer()->landDropsLeft = 1;
	});
	this->registerCallback("nextPhase", [&](Game* game) {
		for (int i = 0; i < sizeof(this->players) / sizeof(Player); i++) {
			this->players[i].emptyManaPool();
		}
	});
	
	
	for (int i = 0; i < sizeof(this->players) / sizeof(Player); i++) {
		for (int c = 0; c < 7; c++) {
			this->players[i].draw();
		}
	}

	int turn = 0;
	while (true) {
		cout << "\n________________\nTurn of player " << this->active + 1 << endl;
		this->turn(turn);
		this->active = this->active == 0 ? 1 : 0;
		turn++;
	}
}
