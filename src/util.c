#include "includes.h"

void Error(const char *function, const char *message)
{
    printf("ERROR: %s\n%s\n", function, message);
    exit(1);
}

void SetPixel(int x, int y, Uint32 color)
{
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
    {
        return;
    }

    Uint32 *pixels = surface->pixels;
    pixels[y * SCREEN_WIDTH + x] = color;
}

void Normalize(Vector3f *vector)
{
    float w = sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
    vector->x /= w;
    vector->y /= w;
    vector->z /= w;
}

float ToRadians(float degrees)
{
    return degrees * (M_PI / 180.0f);
}