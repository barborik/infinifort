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
    for (int k = 0; k < world.dimensions.y; k++)
    {
        for (int i = 0; i < world.dimensions.z; i++)
        {
            for (int j = 0; j < world.dimensions.x; j++)
            {
                SDL_Rect rect;
                rect.x = SCREEN_WIDTH / 2 - (8 * camera.zoom) + (16 * camera.zoom) * j + camera.position.x * 16 * camera.zoom;
                rect.y = SCREEN_HEIGHT / 2 - (9 * camera.zoom) + (18 * camera.zoom) * i + camera.position.z * 18 * camera.zoom - i * 6 * camera.zoom - k * 24;
                rect.w = (16 * camera.zoom);
                rect.h = (18 * camera.zoom);

                Vector3i position;
                position.x = j;
                position.y = k;
                position.z = i;

                int tile = GetTile(world, position);
                SDL_RenderCopy(renderer, textures[tile], NULL, &rect);
            }
        }
    }

    SDL_Rect rect;
    rect.x = SCREEN_WIDTH / 2 - (6 * camera.zoom);
    rect.y = SCREEN_HEIGHT / 2 - (6 * camera.zoom);
    rect.w = 12 * camera.zoom;
    rect.h = 12 * camera.zoom;

    SDL_RenderCopy(renderer, player, NULL, &rect);
}
