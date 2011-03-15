#pragma once
#include "PublicZone.h"

class GameStack : public PublicZone
{
public:
	bool isEmpty();

	void execute();
};

