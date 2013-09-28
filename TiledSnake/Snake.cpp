#include "Snake.h"

Snake::Snake(unsigned headcolor, unsigned segmentcolor, unsigned coincolor)
{
    this->headcolor = headcolor;
    this->segmentcolor = segmentcolor;
    this->coincolor = coincolor;
    Restart();
}

Snake::~Snake()
{
	segments.clear();
}

void Snake::Restart()
{
	segments.clear();
	for(unsigned i = 0; i < START_LENGTH; i++)
	{
		AddSegment(START_X - i, START_Y);
	}

	direction = GO_RIGHT;
	time = 0;
	timeout = 6;
	dead = false;
}

void Snake::AddSegment(unsigned x, unsigned y)
{
	SnakeSegment segment(x, y);
	segments.push_back(segment);
}

void Snake::Update()
{
    if (dead) { return; }

    UpdateInputControls();

    time++;
    if (time < timeout)
    {
        return;
    }

    time = 0;

    if (CheckForWallCollision() || CheckForSelfCollision())
    {
        dead = true;
        return;
    }

    if (CheckForCoinCollision())
    {
        coin.Respawn();
    }
    else
    {
        segments.pop_back();
    }

    MoveSnake();
}

void Snake::UpdateInputControls()
{
    unsigned char* keys = SDL_GetKeyState(NULL);

    if (keys[SDLK_UP] && direction != GO_DOWN)
    {
        direction = GO_UP;
    }
    else if (keys[SDLK_DOWN] && direction != GO_UP)
    {
        direction = GO_DOWN;
    }
    else if (keys[SDLK_LEFT] && direction != GO_RIGHT)
    {
        direction = GO_LEFT;
    }
    else if (keys[SDLK_RIGHT] && direction != GO_LEFT)
    {
        direction = GO_RIGHT;
    }
}

bool Snake::CheckForWallCollision()
{
    unsigned headx = segments[0].x;
    unsigned heady = segments[0].y;

    return (
            (headx == 0) ||
            (heady == 0) ||
            (headx == CELL_WIDTH) ||
            (heady == CELL_HEIGHT));
}

bool Snake::CheckForSelfCollision()
{
    unsigned headx = segments[0].x;
    unsigned heady = segments[0].y;

    for (unsigned i = 1; i < segments.size(); i++)
    {
        if (segments[i].x == headx && segments[i].y == heady)
        {
            return true;
        }
    }
    return false;
}

bool Snake::CheckForCoinCollision()
{
    return (segments[0].x == coin.x && segments[0].y == coin.y);
}

void Snake::MoveSnake()
{
    static const int movex[] = { 0, 0, -1, 1 };
    static const int movey[] = { -1, 1, 0, 0 };

    unsigned x = segments[0].x + movex[direction];
    unsigned y = segments[0].y + movey[direction];

    SnakeSegment nextsegment(x, y);

    segments.push_front(nextsegment);
}

void Snake::Render(SDL_Surface* dest)
{
    if (dead) { return; }

    renderrect.w = CELL_SIZE;
    renderrect.h = CELL_SIZE;

    RenderCoin(dest);
    RenderSnake(dest);
}

void Snake::RenderCoin(SDL_Surface* dest)
{
    renderrect.x = coin.x * CELL_SIZE;
    renderrect.y = coin.y * CELL_SIZE;
    SDL_FillRect(dest, &renderrect, coincolor);
}

void Snake::RenderSnake(SDL_Surface* dest)
{
    renderrect.x = segments[0].x * CELL_SIZE;
    renderrect.y = segments[0].y * CELL_SIZE;
    SDL_FillRect(dest, &renderrect, headcolor);

    for (unsigned i = 1; i < segments.size(); i++)
    {
        renderrect.x = segments[i].x * CELL_SIZE;
        renderrect.y = segments[i].y * CELL_SIZE;
        SDL_FillRect(dest, &renderrect, segmentcolor);
    }
}