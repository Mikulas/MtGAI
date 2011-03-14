#include "Player.h"

Player::Player()
{
	/*this->library = Library();
	this->hand = Hand();
	this->battlefield = PublicZone();
	this->graveyard = PublicZone();
	this->exile = PublicZone();
	this->command = PublicZone();*/
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
