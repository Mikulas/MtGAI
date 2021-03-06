#include "GameStack.h"
#include "Player.h"

GameStack::GameStack()
{
	this->abilities.reserve(100);
	this->cards.reserve(100);
	this->queue.reserve(200);
}

void GameStack::addCard(Card newCard)
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

	this->queue.push_back(0);
}

void GameStack::addAbility(Ability ability)
{
	this->abilities.push_back(ability);
	this->abilities.back().updatePointers();

	this->queue.push_back(1);
}

bool GameStack::isEmpty()
{
	return this->queue.size() == 0;
}

void GameStack::execute()
{
	cout << "EVALUATING STACK:" << endl;
	while (!this->queue.empty()) {
		if (this->queue.back() == 0) {
			cout << "\tcard " << this->cards.back().name << " on stack" << endl;
			this->cards.back().evalute();
			if (this->cards.back().isPermanent())
				this->move(this->cards.back(), &(this->cards.back().controller->battlefield));
			else
				this->move(this->cards.back(), &(this->cards.back().controller->graveyard));
		} else {
			cout << "\tability container on stack" << endl;
			this->abilities.back().evalute();
			this->abilities.pop_back();
		}
		this->queue.pop_back();
	}
	cout << "stack evaluated" << endl << endl;
}
