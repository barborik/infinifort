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

    int frameTime, fps = 0;

    while (1)
    {
        long startTime = SDL_GetTicks64();

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                goto exit;
            }

            Control(event, &camera);
        }

        camera.position.x += moveDelta.x;
        camera.position.y += moveDelta.y;
        camera.position.z += moveDelta.z;

        SDL_RenderClear(renderer);
        Render(camera, world);

        char fpsText[9];
        sprintf(fpsText, "FPS: %d", fps);
        PutString(fpsText, 0, 0, 2);

        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks64() - startTime;
        fps = (frameTime > 1) ? 1000.0f / frameTime : 999;
    }

exit:
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
