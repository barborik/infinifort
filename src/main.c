#include "includes.h"

int main(void)
{
    SDL_Event event;

    World world;
    Camera camera;

    CreateWindow();

    CreateWorld(&world);
    CreateCamera(&camera);

    SDL_SetRelativeMouseMode(SDL_TRUE);

    while (1)
    {
        // float fps;
        // int frame_time, start_time = SDL_GetTicks();

        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                goto exit;
            case SDL_KEYDOWN:
            case SDL_MOUSEMOTION:
                Control(event, &camera);
                continue;
            }
        }

        SDL_FillRect(surface, NULL, 0);

        Render(camera, world);

        SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        // frame_time = SDL_GetTicks() - start_time;
        // fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;

        // printf("%f\n", fps);
    }

exit:
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
