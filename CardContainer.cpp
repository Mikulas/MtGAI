#pragma once
#include "CardContainer.h"

using namespace std;

CardContainer::CardContainer()
{
	this->cards.reserve(100);
}

void CardContainer::addCard(Card card)
{
	bool found = false;
	this->foreach([&](Card *it) {
		if (card == *it)
			found = true;
	});

	if (!found)
		this->cards.push_back(card);
	else
		throw exception("Card with this id already exists in container");
}

// TODO remove this
void CardContainer::foreach(const function<void(Card*)> callback)
{
	for_each(this->cards.begin(), this->cards.end(), [callback](Card card) {callback(&card);} );
}

void CardContainer::move(Card card_moved, CardContainer *container)
{
	this->cards.erase(remove(this->cards.begin(), this->cards.end(), card_moved), this->cards.end());
	container->addCard(card_moved);
}

void CardContainer::print()
{
	this->foreach([&](Card *card) {cout << "\t" << card->name << endl;} );
}

CardContainer::~CardContainer(void)
{
	cout << "Card container cannot be destroyed!\n";
}
