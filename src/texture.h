#ifndef __TILESET_H_
#define __TILESET_H_

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 12

extern SDL_Texture *textures[2];

enum
{
    T_AIR = 0,
    T_GRASS = 1,
};

void LoadTextures(void);
void PutChar(char c, int x, int y, int size);
void PutString(const char *s, int length, int x, int y, int size);

#endif
