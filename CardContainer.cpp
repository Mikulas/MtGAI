#pragma once
#include "CardContainer.h"

using namespace std;

CardContainer::CardContainer()
{
	this->cards.reserve(100);
}

void CardContainer::addCard(Card newCard)
{
	bool found = false;
	for (vector<Card>::iterator card = this->cards.begin(); card != this->cards.end(); card++) {
		if (*card == newCard)
			found = true;
	}

	if (!found)
		this->cards.push_back(newCard);
	else
		throw exception("Card with this id already exists in container");
}

void CardContainer::move(Card card_moved, CardContainer *container)
{
	this->cards.erase(remove(this->cards.begin(), this->cards.end(), card_moved), this->cards.end());
	container->addCard(card_moved);
}

void CardContainer::print()
{
	for (vector<Card>::iterator card = this->cards.begin(); card != this->cards.end(); card++) {
		cout << "\t" << card->name << endl;
	}
}

CardContainer::~CardContainer(void)
{
	cout << "Card container cannot be destroyed!\n";
}
