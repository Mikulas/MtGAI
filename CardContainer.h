#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include "Card.h"

using namespace std;

class Card;

class CardContainer
{
public:
	vector<Card> cards;
	virtual void addCard(Card);
	void foreach(const function<void(Card*)>);
	void move(Card, CardContainer*);
	void print();
	~CardContainer(void);
};
