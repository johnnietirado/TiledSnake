#ifndef SNAKE_H

#define SNAKE_H

#include <iostream>
#include "SDL.h"
#include <deque>
#include "SnakeSegment.h"
#include "Coin.h"

using namespace std;

class Snake
{
private:
	deque<SnakeSegment> segments;
	Coin coin;
	bool dead;
	unsigned direction;
	unsigned time, timeout;
	unsigned headcolor, segmentcolor, coincolor;
	SDL_Rect renderRect;

public:
	Snake(unsigned headcolor, unsigned segmentcolor, unsigned coincolor);
	~Snake();
	void Restart();
	void Update();
	void Render(SDL_Surface* dest);
	inline bool IsDead() {return dead;};

private:
	void UpdateInputControls();
    void RenderSnake(SDL_Surface* dest);
    void RenderCoin(SDL_Surface* dest);
    void AddSegment(unsigned x, unsigned y);
    void MoveSnake();
    bool CheckForWallCollision();
    bool CheckForSelfCollision();
    bool CheckForCoinCollision();

};

#endif