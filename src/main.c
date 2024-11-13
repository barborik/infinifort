#include "includes.h"

int main(void)
{
    World world;
    Camera camera;
    SDL_Event event;

    // pthread_t renderThread;
    // pthread_create(&renderThread, NULL, Render, NULL);

    CreateWindow();

    CreateWorld(&world);
    CreateCamera(&camera);

    LoadTextures();

    // SDL_SetRelativeMouseMode(SDL_TRUE);

    while (1)
    {
        int fps, frameTime, startTime = SDL_GetTicks();

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

        SDL_RenderClear(renderer);
        Render(camera, world);

        char fpsText[8];
        memset(fpsText, 0, 8);
        sprintf(fpsText, "FPS: %d", fps);
        PutString(fpsText, 8, 0, 0, 2);

        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - startTime;
        fps = (frameTime > 1) ? 1000.0f / frameTime : 999;
    }

exit:
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
