#include "includes.h"

void CreateCamera(Camera *camera)
{
    Vector3f position;

    position.x = 0.0f;
    position.y = 0.0f;
    position.z = 0.0f;

    camera->fov = 90.0f;
    camera->yaw = 0.0f;
    camera->pitch = 0.0f;
    camera->position = position;
}

#define EPSILON 1e-6
#define MAX_STEPS 10

// https://voxel.wiki/wiki/raycasting/
int CastRay(Vector3f origin, Vector3f direction, World world, int debug)
{
    Normalize(&direction);

    if (direction.x == 0.0f) direction.x = EPSILON;
    if (direction.y == 0.0f) direction.y = EPSILON;
    if (direction.z == 0.0f) direction.z = EPSILON;

    Vector3f signf;
    signf.x = (direction.x >= 0.0f) ? 1.0f : -1.0f;
    signf.y = (direction.y >= 0.0f) ? 1.0f : -1.0f;
    signf.z = (direction.z >= 0.0f) ? 1.0f : -1.0f;

    Vector3i sign;
    sign.x = signf.x;
    sign.y = signf.y;
    sign.z = signf.z;

    Vector3f step;
    step.x = 1.0f / direction.x;
    step.y = 1.0f / direction.y;
    step.z = 1.0f / direction.z;

    Vector3f originGrid;
    originGrid.x = floorf(origin.x);
    originGrid.y = floorf(origin.y);
    originGrid.z = floorf(origin.z);

    Vector3i voxelPosition;
    voxelPosition.x = originGrid.x;
    voxelPosition.y = originGrid.y;
    voxelPosition.z = originGrid.z;

    Vector3f sideDistance;
    sideDistance.x = (originGrid.x - origin.x + 0.5f + signf.x * 0.5f) * step.x;
    sideDistance.y = (originGrid.y - origin.y + 0.5f + signf.y * 0.5f) * step.y;
    sideDistance.z = (originGrid.z - origin.z + 0.5f + signf.z * 0.5f) * step.z;

    Vector3i mask;

    for (int i = 0; i < MAX_STEPS; i++)
    {
        if (debug)
        {
            printf("VOXEL %d %d %d\n", voxelPosition.x, voxelPosition.y, voxelPosition.z);
        }

        int voxel = GetVoxel(world, voxelPosition);

        if (voxel != 0)
        {
            if (debug)
            {
                printf("==========\n");
            }
            return voxel;
        }

        mask.x = sideDistance.x <= ((sideDistance.y < sideDistance.z) ? sideDistance.y : sideDistance.z);
        mask.y = sideDistance.y <= ((sideDistance.z < sideDistance.x) ? sideDistance.z : sideDistance.x);
        mask.z = sideDistance.z <= ((sideDistance.x < sideDistance.y) ? sideDistance.x : sideDistance.y);

        sideDistance.x += mask.x * step.x;
        sideDistance.y += mask.y * step.y;
        sideDistance.z += mask.z * step.z;

        voxelPosition.x += mask.x * sign.x;
        voxelPosition.y += mask.y * sign.y;
        voxelPosition.z += mask.z * sign.z;
    }

    if (debug)
    {
        printf("==========\n");
    }
    return 0;
}

extern int debug_x, debug_y, debug;

void Render(Camera camera, World world)
{
    float scale = tan(ToRadians(camera.fov * 0.5f));
    float aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

    // euler angles to direction vector
    Vector3f directionOffset;
    directionOffset.x = cos(camera.pitch) * cos(camera.yaw);
    directionOffset.y = sin(camera.pitch);
    directionOffset.z = cos(camera.pitch) * sin(camera.yaw);

    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            Vector3f direction;
            direction.x = (2 * (j + 0.5f) / (float)SCREEN_WIDTH - 1) * aspectRatio * scale;
            direction.y = (1 - 2 * (i + 0.5f) / (float)SCREEN_HEIGHT) * scale;
            direction.z = 1;

            if (debug && debug_x == j && debug_y == i)
            {
                CastRay(camera.position, direction, world, 1);
                debug = 0;
            }

            int voxel = CastRay(camera.position, direction, world, 0);

            if (voxel != 0)
            {
                SetPixel(j, i, 0xff0000ff);
            }
        }
    }

    // printf("======\n");
}
