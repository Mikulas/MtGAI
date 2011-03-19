#include "Player.h"

Player::Player()
{
	this->passed = false;
	this->canDraw = true;
	this->life = 20;
	this->poison = 0;
	this->landDropsLeft = 1;
	this->emptyManaPool();
}

void Player::emptyManaPool()
{
	for (int i = 0; i < sizeof(this->mana) / sizeof(int); i++) {
		this->mana[i] = 0;
	}
}

void Player::play(bool sorcery)
{
	cout << "What card do you want to play?" << endl;
	int index = 1;
	cout << "  [0] /pass/" << endl;

	vector<Card> cards;
	int abilities_size = 0;
	for (vector<Card>::iterator it = this->battlefield.cards.begin(); it != this->battlefield.cards.end(); ++it) {
		Card card = *it;
		vector<pair<string, string>> ability = card.permanentAbilities();
		for (vector<pair<string, string>>::iterator it = ability.begin(); it != ability.end(); ++it) {
			cout << "  [" << index << "] " << card.name << " - " << it->first << ": " << it->second << endl;
			index++;
			abilities_size++;
		}
	};
	if (sorcery) {
		this->hand.foreach([&](Card *card) {
			if (this->landDropsLeft > 0 || !card->hasType("land")) {
				cards.push_back(*card);
				cout << "  [" << index << "] " << card->name << " [";
				card->printCost();
				cout << "]" << endl;
				index++;
			}
		});
	} else {
		this->hand.foreach([&](Card *card) {
			if (card->isInstant()) {
				cards.push_back(*card);
				cout << "  [" << index << "] " << card->name << " [";
				card->printCost();
				cout << "]" << endl;
				index++;
			}
		});
	}
	string buffer;
	getline(cin, buffer); // intentionally so that \n is treated as 0
	int choice = atoi(buffer.c_str());
	if (choice == 0) {
		cout << "passed" << endl;
		this->passed = true;
	} else if (choice <= abilities_size) {
		int index = 0;
		for (vector<Card>::iterator it = this->battlefield.cards.begin(); it != this->battlefield.cards.end(); ++it) {
			Card card = *it;
			vector<pair<string, string>> ability = card.permanentAbilities();
			for (vector<pair<string, string>>::iterator it = ability.begin(); it != ability.end(); ++it) {
				if (index == choice - 1) {
					//cout << card.name << " - " << it->first << ": " << it->second << endl;
					Effect effect;
					effect.effect = it->second;
					EffectContainer effects(this);
					effects.addEffect(effect);
					this->stack->addEffect(effects);
					return;
				}
				index++;
			}
		};
	} else {
		Card card = cards[choice - abilities_size - 1];
		if (card.hasType("land")) {
			this->landDropsLeft--;
			this->hand.move(card, &this->battlefield); // Lands do not stack
			//this->battlefield.cards.back().callback("enterBattlefield", &(this->battlefield.cards.back()));
		} else {
			this->hand.move(card, this->stack);
		}
	}
}

void Player::draw()
{
	Card card = this->library.cards.back();
	this->library.move(card, &this->hand);
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
