#ifndef __TYPES_H_
#define __TYPES_H_

typedef struct
{
    int x, y, z;
} Vector3i;

typedef struct
{
    float x, y, z;
} Vector3f;

typedef struct
{
    float zoom;
    Vector3f position;
} Camera;

typedef struct
{
    uint8_t *tiles;
    Vector3i dimensions;
} World;

#endif
