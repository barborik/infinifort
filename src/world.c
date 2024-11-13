#include "includes.h"

void CreateWorld(World *world)
{
    Vector3i dimensions;

    dimensions.x = 8;
    dimensions.y = 8;
    dimensions.z = 8;

    world->dimensions = dimensions;
    world->tiles = malloc(dimensions.x * dimensions.y * dimensions.z);
    memset(world->tiles, 0, dimensions.x * dimensions.y * dimensions.z);

    Vector3i position;

    position.x = 0;
    position.y = 0;
    position.z = 0;
    SetTile(*world, position, T_GRASS);

    position.x = 1;
    position.y = 0;
    position.z = 0;
    SetTile(*world, position, T_GRASS);

    position.x = 0;
    position.y = 0;
    position.z = 1;
    SetTile(*world, position, T_GRASS);
}

int GetTile(World world, Vector3i position)
{
    if (position.x < 0 || position.x >= world.dimensions.x ||
        position.y < 0 || position.y >= world.dimensions.y ||
        position.z < 0 || position.z >= world.dimensions.z)
    {
        return 0;
    }

    int yOffset = position.y * world.dimensions.x * world.dimensions.z;
    int zOffset = position.z * world.dimensions.x;
    return world.tiles[yOffset + zOffset + position.x];
}

void SetTile(World world, Vector3i position, int tile)
{
    if (position.x < 0 || position.x >= world.dimensions.x ||
        position.y < 0 || position.y >= world.dimensions.y ||
        position.z < 0 || position.z >= world.dimensions.z)
    {
        return;
    }

    int yOffset = position.y * world.dimensions.x * world.dimensions.z;
    int zOffset = position.z * world.dimensions.x;
    world.tiles[yOffset + zOffset + position.x] = tile;
}
