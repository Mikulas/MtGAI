#include "Player.h"

Player::Player()
{
	this->passed = false;
	this->canDraw = true;
	this->life = 20;
	this->poison = 0;
	this->landDropsLeft = 1;
	this->emptyManaPool();
}

void Player::emptyManaPool()
{
	for (int i = 0; i < sizeof(this->mana) / sizeof(int); i++) {
		this->mana[i] = 0;
	}
}

void Player::play(bool sorcery)
{
	cout << "What card do you want to play?" << endl;
	int index = 1;
	cout << "[0] /pass/" << endl;
	vector<Card> cards;
	if (sorcery) {
		this->hand.foreach([&](Card *card) {
			if (this->landDropsLeft > 0 || !card->hasType("land")) {
				cards.push_back(*card);
				cout << "[" << index << "] " << card->name << endl;
				index++;
			}
		});
	} else {
		this->hand.foreach([&](Card *card) {
			if (card->isInstant()) {
				cards.push_back(*card);
				cout << "[" << index << "] " << card->name << endl;
				index++;
			}
		});
	}
	int choice = 0;
	scanf("%d", &choice);
	if (choice == 0) {
		cout << "passed" << endl;
		this->passed = true;
	} else {
		Card card = cards[choice - 1];
		if (card.hasType("land")) {
			this->landDropsLeft--;
			this->hand.move(card, this->battlefield); // Lands do not stack
		} else {
			this->hand.move(card, *this->stack);
		}
	}
}

void Player::draw()
{
	Card card = this->library.cards.back();
	this->library.move(card, this->hand);
}

void Player::print()
{
	cout << "library:\n";
	this->library.print();
	cout << "hand:\n";
	this->hand.print();
	cout << "battlefield:\n";
	this->battlefield.print();
	cout << "graveyard:\n";
	this->graveyard.print();
	cout << "exile:\n";
	this->exile.print();
	cout << "command:\n";
	this->command.print();
}
