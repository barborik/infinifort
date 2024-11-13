#include "includes.h"

SDL_Window *window;
SDL_Renderer *renderer;

void CreateWindow(void)
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        Error("SDL_Init()", SDL_GetError());
    }

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window)
    {
        Error("SDL_CreateWindow()", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
