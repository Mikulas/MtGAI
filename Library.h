#pragma once
#include <vector>
#include "Card.h"
#include "HiddenZone.h"

class Library : public HiddenZone
{
public:
	void shuffle();
};
