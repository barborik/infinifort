#include "includes.h"

typedef struct
{
    Camera camera;
    World world;
    int start, end;
} ThreadArgs;

int nThreads = 8;
pthread_t threads[8];

void CreateCamera(Camera *camera)
{
    Vector3f position;

    position.x = 0.5f;
    position.y = 4.0f;
    position.z = 0.5f;

    camera->fov = 70.0f;
    camera->yaw = 0.0f;
    camera->pitch = 0.0f;
    camera->position = position;
}

#define MAX_STEPS 64

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
}

void *RenderRows(void *args)
{
    ThreadArgs *data = args;

    float scale = tan(ToRadians(data->camera.fov * 0.5f));
    float aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

    for (int i = data->start; i < data->end; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            Vector3f direction;
            direction.x = (2 * (j + 0.5f) / (float)SCREEN_WIDTH - 1) * aspectRatio * scale;
            direction.y = (1 - 2 * (i + 0.5f) / (float)SCREEN_HEIGHT) * scale;
            direction.z = 1.0f;

            RotateZ(&direction, data->camera.pitch);
            RotateY(&direction, data->camera.yaw);

            int voxel = CastRay(data->camera.position, direction, data->world);

            if (voxel != 0)
            {
                SetPixel(j, i, 0xff0000ff);
            }
        }
    }

    return NULL;
}

void Render(Camera camera, World world)
{
    int linesPerThread = SCREEN_HEIGHT / nThreads;

    ThreadArgs args[nThreads];

    for (int i = 0; i < nThreads; i++)
    {
        args[i].camera = camera;
        args[i].world = world;
        args[i].start = linesPerThread * i;
        args[i].end = linesPerThread * i + linesPerThread;

        pthread_create(&(threads[i]), NULL, RenderRows, &(args[i]));
    }

    for (int i = 0; i < nThreads; i++)
    {
        pthread_join(threads[i], NULL);
    }
}
