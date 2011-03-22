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
		vector<Ability> abilities = card.getAbilities();
		for (vector<Ability>::iterator ability = abilities.begin(); ability != abilities.end(); ++ability) {
			if (ability->isCastable(this)) {
				cout << "  [" << index << "] " << card.name << " - ";
				for (vector<string>::iterator cost = ability->cost.begin(); cost != ability->cost.end();) {
					cout << *cost;
					cost++;
					if (cost != ability->cost.end())
						cout << ", ";
				}
				cout << ": ";
				for (vector<Effect>::iterator effect = ability->effects.begin(); effect != ability->effects.end();) {
					cout << effect->effect;
					effect++;
					if (effect != ability->effects.end())
						cout << ", ";
				}
				cout << endl;
				index++;
				abilities_size++;
			} else {
				cout << "  [_] " << card.name << " - ";
				for (vector<string>::iterator cost = ability->cost.begin(); cost != ability->cost.end();) {
					cout << *cost;
					cost++;
					if (cost != ability->cost.end())
						cout << ", ";
				}
				cout << ": ";
				for (vector<Effect>::iterator effect = ability->effects.begin(); effect != ability->effects.end();) {
					cout << effect->effect;
					effect++;
					if (effect != ability->effects.end())
						cout << ", ";
				}
				cout << endl;
			}
		}
	};
	this->hand.foreach([&](Card *card) {
		if ((!sorcery && card->isInstant()) || (sorcery && (this->landDropsLeft > 0 || !card->hasType("land")))) {
			if (card->isCastable(this)) {
				cards.push_back(*card);
				cout << "  [" << index << "] {";
				card->printCost();
				cout << "}: "<< card->name << endl;
				index++;
			} else {
				cout << "  [_] {";
				card->printCost();
				cout << "}: " << card->name << endl;
			}
		}
	});

	string buffer;
	getline(cin, buffer); // intentionally so that merely \n is treated as 0
	int choice = atoi(buffer.c_str());
	if (choice == 0) {
		cout << "passed" << endl;
		this->passed = true;
	} else if (choice <= abilities_size) {
		int index = 0;
		for (vector<Card>::iterator it = this->battlefield.cards.begin(); it != this->battlefield.cards.end(); ++it) {
			vector<Ability> abilities = it->getAbilities();
			for (vector<Ability>::iterator ability = abilities.begin(); ability != abilities.end(); ++ability) {
				if (!ability->isCastable(this)) break;
				if (index == choice - 1) {
					ability->payCost(this);
					ability->caster = this->game->getPriorityPlayer(); // persistent pointer to this
					ability->card = &*it;
					if (ability->isManaAbility()) { // do not stack
						ability->updatePointers();
						ability->evalute();
					} else {
						this->game->stack.addAbility(*ability);
						//this->game->stack.abilities.back().card = &(*it);
					}
					return;
				}
				index++;
			}
		}
	} else {
		Card card = cards[choice - abilities_size - 1];
		card.controller = this->game->getPriorityPlayer(); // persistent pointer to this
		if (card.hasType("land")) {
			this->landDropsLeft--;
			this->hand.move(card, &this->battlefield); // Lands do not stack
			//this->battlefield.cards.back().callback("enterBattlefield", &(this->battlefield.cards.back()));
		} else {
			card.payCost(this);
			this->hand.move(card, &this->game->stack);
			cout << "card " << card.name << " moved to stack" << endl;
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

int Player::getManaSum(bool snowOnly)
{
	int snow[] = {SnowForest, SnowIsland, SnowMountain, SnowPlains, SnowSwamp, SnowColorless, SnowMulticolor};
	int sum = 0;
	if (snowOnly) {
		for (int i = 0; i < sizeof(snow) / sizeof(int); i++) { /** @todo verify that this works */
			sum += this->mana[snow[i]];
		}
	} else {
		for (int i = 0; i < sizeof(this->mana) / sizeof(int); i++) {
			sum += this->mana[i];
		}
	}
	return sum;
}
