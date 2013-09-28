#ifndef COIN_H

#define COIN_H

#include <iostream>
#include "Defines.h"

class Coin
{
public:
	unsigned x;
	unsigned y;

	Coin();

	void Respawn();
};

#endif