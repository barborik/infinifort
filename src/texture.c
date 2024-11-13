#include "includes.h"

SDL_Texture *font;
SDL_Texture *textures[2];

void LoadTextures(void)
{
    font = IMG_LoadTexture(renderer, "res/dsc8x12.bmp");

    textures[T_AIR] = IMG_LoadTexture(renderer, "res/air.png");
    textures[T_GRASS] = IMG_LoadTexture(renderer, "res/grass.png");
}

void PutChar(char c, int x, int y, int size)
{
    SDL_Rect source, destination;

    source.x = c * CHAR_WIDTH;
    source.y = 0;
    source.w = CHAR_WIDTH;
    source.h = CHAR_HEIGHT;

    destination.x = x;
    destination.y = y;
    destination.w = CHAR_WIDTH * size;
    destination.h = CHAR_HEIGHT * size;

    SDL_RenderCopy(renderer, font, &source, &destination);
}

void PutString(const char *s, int length, int x, int y, int size)
{
    for (int i = 0; i < length; i++)
    {
        PutChar(s[i], x + i * CHAR_WIDTH * size, y, size);
    }
}
