#include "includes.h"

void CreateCamera(Camera *camera)
{
    Vector3f position;

    position.x = 0.0f;
    position.y = 0.0f;
    position.z = 0.0f;

    camera->fov = 70.0f;
    camera->yaw = 0.0f;
    camera->pitch = 0.0f;
    camera->position = position;
}

#define MAX_STEPS 10

int CastRay(Vector3f origin, Vector3f direction, World world)
{
    Vector3i voxelPosition = {
        (int)floor(origin.x),
        (int)floor(origin.y),
        (int)floor(origin.z)};

    Vector3i step = {
        (direction.x >= 0.0f) ? 1 : -1,
        (direction.y >= 0.0f) ? 1 : -1,
        (direction.z >= 0.0f) ? 1 : -1};

    Vector3f tDelta = {
        (direction.x != 0.0f) ? fabs(1.0f / direction.x) : INFINITY,
        (direction.y != 0.0f) ? fabs(1.0f / direction.y) : INFINITY,
        (direction.z != 0.0f) ? fabs(1.0f / direction.z) : INFINITY};

    Vector3f tMax = {
        (direction.x != 0.0f) ? (step.x > 0 ? (floor(origin.x + 1) - origin.x) : (origin.x - floor(origin.x))) * tDelta.x : INFINITY,
        (direction.y != 0.0f) ? (step.y > 0 ? (floor(origin.y + 1) - origin.y) : (origin.y - floor(origin.y))) * tDelta.y : INFINITY,
        (direction.z != 0.0f) ? (step.z > 0 ? (floor(origin.z + 1) - origin.z) : (origin.z - floor(origin.z))) * tDelta.z : INFINITY};

    for (int i = 0; i < MAX_STEPS; i++)
    {
        int voxel = GetVoxel(world, voxelPosition);
        if (voxel != 0)
        {
            return voxel;
        }

        if (tMax.x < tMax.y)
        {
            if (tMax.x < tMax.z)
            {
                voxelPosition.x += step.x;
                tMax.x += tDelta.x;
            }
            else
            {
                voxelPosition.z += step.z;
                tMax.z += tDelta.z;
            }
        }
        else
        {
            if (tMax.y < tMax.z)
            {
                voxelPosition.y += step.y;
                tMax.y += tDelta.y;
            }
            else
            {
                voxelPosition.z += step.z;
                tMax.z += tDelta.z;
            }
        }
    }

    return 0;

    /*Normalize(&direction);

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
    return 0;*/
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

void Render(Camera camera, World world)
{
    float scale = tan(ToRadians(camera.fov * 0.5f));
    float aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            Vector3f direction;
            direction.x = (2 * (j + 0.5f) / (float)SCREEN_WIDTH - 1) * aspectRatio * scale;
            direction.y = (1 - 2 * (i + 0.5f) / (float)SCREEN_HEIGHT) * scale;
            direction.z = 1.0f;

            RotateZ(&direction, camera.pitch);
            RotateY(&direction, camera.yaw);

            int voxel = CastRay(camera.position, direction, world);

            if (voxel != 0)
            {
                SetPixel(j, i, 0xff0000ff);
            }
        }
    }
}
