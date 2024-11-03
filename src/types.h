#ifndef __TYPES_
#define __TYPES_

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
    uint8_t *grid;
    Vector3i dimensions;
} World;

typedef struct
{
    float fov;
    float yaw, pitch;
    Vector3f position;
} Camera;

#endif
