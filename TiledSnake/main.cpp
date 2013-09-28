#include "SDL.h"
#include <iostream>
#include "Defines.h"
#include "Snake.h"

using namespace std;



int main(int argc, char* args[])
{
	SDL_Surface* displaysurface = NULL;
	SDL_Event sdlevent;
	unsigned boxcolor;
	
	bool running;
	
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cerr << "SDL_Init Failed: " << SDL_GetError() << endl;	
		return -1;
	}

	displaysurface = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if(displaysurface == NULL)
	{
		cerr << "SDL_SetVideoMode Failed: " << SDL_GetError() << endl;
		return -1;
	}

	SDL_WM_SetCaption("Tiled Snake", NULL);



	unsigned backgroundcolor = SDL_MapRGB(displaysurface->format, 0, 64, 0);
	unsigned snakeheadcolor = SDL_MapRGB(displaysurface->format, 255, 0, 0);
	unsigned snakebodycolor = SDL_MapRGB(displaysurface->format, 0, 255, 0);
	unsigned coincolor = SDL_MapRGB(displaysurface->format, 255, 255, 0);

	Snake snake(snakeheadcolor, snakebodycolor, coincolor);

	boxcolor = SDL_MapRGB(displaysurface->format, 255, 0, 0);
	running  = true;

	while(running)
	{
		while(SDL_PollEvent(&sdlevent))
		{
			//handle events
			//render game
			switch(sdlevent.type)
			{
			case SDL_QUIT:
				{
					running = false;
				}
				break;
			case SDL_KEYDOWN:
				{
					if(sdlevent.key.keysym.sym == SDLK_ESCAPE)
					{
						running = false;
					}
					if(sdlevent.key.keysym.sym == SDLK_RETURN)
					{
						if(snake.IsDead())
							snake.Restart();
					}
				}
				break;
			}
		}
		snake.Update();
		SDL_FillRect(displaysurface, NULL, backgroundcolor);
		snake.Render(displaysurface);
		SDL_Flip(displaysurface);
		SDL_Delay(20);
	}

	SDL_Quit();

	return 0;
}