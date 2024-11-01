#include "includes.h"

int debug_x, debug_y, debug = 0;

int main(void)
{
    SDL_Event event;

    World world;
    Camera camera;

    CreateWindow();

    CreateWorld(&world);
    CreateCamera(&camera);

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
            case SDL_MOUSEBUTTONDOWN:
                debug = 1;
                SDL_GetMouseState(&debug_x, &debug_y);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_w:
                    camera.position.x += 0.1f;
                    break;
                case SDLK_s:
                    camera.position.x -= 0.1f;
                    break;
                case SDLK_a:
                    camera.position.z -= 0.1f;
                    break;
                case SDLK_d:
                    camera.position.z += 0.1f;
                    break;
                case SDLK_LEFT:
                    camera.direction.x -= 0.1f;
                    break;
                case SDLK_RIGHT:
                    camera.direction.x += 0.1f;
                    break;
                case SDLK_UP:
                    camera.direction.y -= 0.1f;
                    break;
                case SDLK_DOWN:
                    camera.direction.y += 0.1f;
                    break;
                case SDLK_SPACE:
                    camera.position.y += 0.1f;
                    break;
                case SDLK_LSHIFT:
                    camera.position.y -= 0.1f;
                    break;
                }
                break;
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
