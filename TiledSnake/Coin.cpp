#include "Coin.h"


Coin::Coin()
{
	Respawn();
}

void Coin::Respawn()
{
	x = 1 + rand() % (CELL_WIDTH - 2);
	y = 1 + rand() % (CELL_HEIGHT - 2);
}
