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
        float fps;
        int frame_time, start_time = SDL_GetTicks();

        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                goto exit;
            case SDL_MOUSEMOTION:
                camera.yaw += 0.0025f * event.motion.xrel;
                camera.pitch += 0.0025f * event.motion.yrel;
                continue;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_w:
                    camera.position.z += 0.1f;
                    continue;
                case SDLK_s:
                    camera.position.z -= 0.1f;
                    continue;
                case SDLK_a:
                    camera.position.x -= 0.1f;
                    continue;
                case SDLK_d:
                    camera.position.x += 0.1f;
                    continue;
                case SDLK_LEFT:
                    camera.yaw -= 0.1f;
                    continue;
                case SDLK_RIGHT:
                    camera.yaw += 0.1f;
                    continue;
                case SDLK_UP:
                    camera.pitch -= 0.1f;
                    continue;
                case SDLK_DOWN:
                    camera.pitch += 0.1f;
                    continue;
                case SDLK_SPACE:
                    camera.position.y += 0.1f;
                    continue;
                case SDLK_LSHIFT:
                    camera.position.y -= 0.1f;
                    continue;
                }
                continue;
            }
        }

        SDL_FillRect(surface, NULL, 0);

        Render(camera, world);

        SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        frame_time = SDL_GetTicks() - start_time;
        fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;

        // printf("%f\n", fps);
    }

exit:
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
