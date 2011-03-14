#include "Library.h"


void Library::shuffle()
{
	random_shuffle(this->cards.begin(), this->cards.end());
}
