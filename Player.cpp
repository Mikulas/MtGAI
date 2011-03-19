#include "Player.h"
#include "Game.h"

Player::Player()
{
	this->passed = false;
	this->canDraw = true;
	this->life = 20;
	this->poison = 0;
	this->landDropsLeft = 1;
	this->emptyManaPool();
}

void Player::setMana(Mana index, int value)
{
	this->mana[index] += value;
	this->mana[index] = this->mana[index] < 0 ? 0 : this->mana[index];
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
	this->hand.foreach([&](Card *card) {
		if ((!sorcery && card->isInstant()) || (sorcery && (this->landDropsLeft > 0 || !card->hasType("land")))) {
			cards.push_back(*card);
			cout << "  [" << index << " " << (card->isCastable(this) ? "y" : "n") << "] " << card->name << " [";
			card->printCost();
			cout << "]" << endl;
			index++;
		}
	});

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
					Ability ability(&this->game->players[this->id]); // persistent pointer
					this->game->stack.addAbility(ability);
					Effect effect;
					effect.effect = it->second;
					this->game->stack.abilities.back().addEffect(effect);
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
			this->hand.move(card, &this->game->stack);
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
	cout << "mana: ";
	for (int i = 0; i < sizeof(this->mana) / sizeof(int); i++) {
		cout << this->mana[i] << ", ";
	}
	cout << endl;
}
