#include "includes.h"

void CreateCamera(Camera *camera)
{
    Vector3f position;

    position.x = 0.0f;
    position.y = 0.0f;
    position.z = 0.0f;

    camera->zoom = 4.0f;
    camera->position = position;
}

void Render(Camera camera, World world)
{
    for (int i = 0; i < world.dimensions.z; i++)
    {
        for (int j = 0; j < world.dimensions.x; j++)
        {
            SDL_Rect rect;
            rect.x = (16 * camera.zoom) * j + camera.position.x * 16 * camera.zoom;
            rect.y = (16 * camera.zoom) * i + camera.position.z * 16 * camera.zoom;
            rect.w = (16 * camera.zoom);
            rect.h = (16 * camera.zoom);

            Vector3i position;
            position.x = j;
            position.y = camera.position.y;
            position.z = i;

            int tile = GetTile(world, position);
            SDL_RenderCopy(renderer, textures[tile], NULL, &rect);
        }
    }
}
