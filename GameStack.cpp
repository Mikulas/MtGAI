#include "GameStack.h"
#include "Player.h"

void GameStack::addCard(Card card)
{
	bool found = false;
	this->foreach([&](Card *it) {
		if (card == *it) {
			found = true;
		}
	});

	if (!found)
		this->cards.push_back(card);
	else
		throw exception("Card with this id already exists in container");

	this->queue.push_back(0);
}

void GameStack::addAbility(Ability ability)
{
	this->abilities.push_back(ability);
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
			//this->cards.pop_back(); // move maintained by evalute
		} else {
			cout << "\tability container on stack" << endl;
			this->abilities.back().evalute();
			this->abilities.pop_back();
		}
		this->queue.pop_back();
	}
	cout << "stack evaluated" << endl << endl;
}
