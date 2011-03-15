#pragma once
#include "HiddenZone.h"

class Hand : public HiddenZone
{
public:
	void discard(int count = 1);
};

