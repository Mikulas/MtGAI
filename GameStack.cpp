#include "GameStack.h"

void GameStack::addCard(Card card)
{
	CardContainer::addCard(card);
	this->queue.push_back(0);
}

void GameStack::addEffect(EffectContainer effects)
{
	this->effects.push_back(effects);
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
			cout << "\tcard on stack" << endl;
			this->cards.back().evalute();
			//this->cards.pop_back(); // move maintained by evalute
		} else {
			cout << "\teffect container on stack" << endl;
			this->effects.back().evalute();
			this->effects.pop_back();
		}
		this->queue.pop_back();
	}
	cout << "stack evaluated" << endl << endl;
}
