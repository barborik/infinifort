#include "includes.h"

void CreateWorld(World *world)
{
    Vector3i dimensions;

    dimensions.x = 8;
    dimensions.y = 8;
    dimensions.z = 8;

    world->dimensions = dimensions;
    world->grid = malloc(dimensions.x * dimensions.y * dimensions.z);
    memset(world->grid, 0, dimensions.x * dimensions.y * dimensions.z);

    Vector3i position;

    position.x = 0;
    position.y = 1;
    position.z = 0;
    SetVoxel(*world, position, 1);

    position.x = 1;
    position.y = 1;
    position.z = 0;
    SetVoxel(*world, position, 1);

    position.x = 0;
    position.y = 1;
    position.z = 1;
    SetVoxel(*world, position, 1);

    position.x = 1;
    position.y = 1;
    position.z = 1;
    SetVoxel(*world, position, 1);

    position.x = 2;
    position.y = 1;
    position.z = 2;
    SetVoxel(*world, position, 1);


    position.x = 2;
    position.y = 1;
    position.z = 1;
    SetVoxel(*world, position, 1);
}

int GetVoxel(World world, Vector3i position)
{
    if (position.x < 0 || position.x >= world.dimensions.x ||
        position.y < 0 || position.y >= world.dimensions.y ||
        position.z < 0 || position.z >= world.dimensions.z)
    {
        return 0;
    }

    int yOffset = position.y * world.dimensions.x * world.dimensions.z;
    int zOffset = position.z * world.dimensions.x;
    return world.grid[yOffset + zOffset + position.x];
}

void SetVoxel(World world, Vector3i position, int voxel)
{
    if (position.x < 0 || position.x >= world.dimensions.x ||
        position.y < 0 || position.y >= world.dimensions.y ||
        position.z < 0 || position.z >= world.dimensions.z)
    {
        return;
    }

    int yOffset = position.y * world.dimensions.x * world.dimensions.z;
    int zOffset = position.z * world.dimensions.x;
    world.grid[yOffset + zOffset + position.x] = voxel;
}
