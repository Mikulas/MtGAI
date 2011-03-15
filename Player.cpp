#include "Player.h"

Player::Player()
{
	/*this->library = Library();
	this->hand = Hand();
	this->battlefield = PublicZone();
	this->graveyard = PublicZone();
	this->exile = PublicZone();
	this->command = PublicZone();*/
	this->passed = false;
	this->canDraw = true;
}

void Player::play()
{
	/* play or set passed to true*/
	if (rand() % 2 == 0) {
		this->passed = true;
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
