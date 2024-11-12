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

void Euler2Vector3f(float yaw, float pitch, Vector3f *vector)
{
    vector->x = cos(pitch) * sin(yaw);
    vector->y = -sin(pitch);
    vector->z = cos(pitch) * cos(yaw);
}

void AddVector3f(Vector3f a, Vector3f b, Vector3f *result)
{
    result->x = a.x + b.x;
    result->y = a.y + b.y;
    result->z = a.z + b.z;
}

void ScaleVector3f(Vector3f *v, float factor)
{
    v->x *= factor;
    v->y *= factor;
    v->z *= factor;
}

void RotateY(Vector3f *vector, float angle)
{
    float x = cos(angle) * vector->x + sin(angle) * vector->z;
    float z = -sin(angle) * vector->x + cos(angle) * vector->z;

    vector->x = x;
    vector->z = z;
}

void RotateZ(Vector3f *vector, float angle)
{
    float y = cos(angle) * vector->y - sin(angle) * vector->z;
    float z = sin(angle) * vector->y + cos(angle) * vector->z;

    vector->y = y;
    vector->z = z;
}

float ToRadians(float degrees)
{
    return degrees * (M_PI / 180.0f);
}