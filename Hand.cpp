#include "Hand.h"

void Hand::discard(int count)
{
	/** @todo implement player choice */
	if (count <= 0)
		throw new exception("Invalid count given, expected positive integer");
	cout << "player is discarding a card" << endl;
	for (int i = 0; i < count; i++) {
		this->cards.pop_back();
	}
}
