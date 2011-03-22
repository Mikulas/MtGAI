#include "Hand.h"

void Hand::discard(int count)
{
	if (count <= 0)
		throw new exception("Invalid count given, expected positive integer");

	cout << "what card do you want to discard?\n";
	for (int i = 0; i < count; i++) { // almost always one
		int index = 0;
		for (vector<Card>::iterator card = this->cards.begin(); card != this->cards.end(); card++) {
			cout << "[" << index << "] " << card->name << endl;
			index++;
		}
		
		string buffer;
		int choice;
		do {
			getline(cin, buffer);
			choice = atoi(buffer.c_str());
		} while (choice < 0 || choice > index);

		this->cards.erase(this->cards.begin() + choice);
	}
}
