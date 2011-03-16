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
	int card_index = this->cards.size() - 1;
	int effect_index = this->effects.size() - 1;
	for (int i = this->queue.size() - 1; i >= 0; i--) {
		if (this->queue[i] == 0) {
			cout << "\tcard on stack" << this->cards[card_index].name << endl;
			card_index--;
		} else {
			cout << "\teffect contaienr on stack" << endl;
			effect_index--;
		}
	}
	cout << "stack evaluated" << endl << endl;
}
