#include "includes.h"

void Control(SDL_Event event, Camera *camera)
{
    switch (event.type)
    {
    case SDL_MOUSEMOTION:
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            camera->position.z -= 0.2f;
            break;
        case SDLK_s:
            camera->position.z += 0.2f;
            break;
        case SDLK_a:
            camera->position.x -= 0.2f;
            break;
        case SDLK_d:
            camera->position.x += 0.2f;
            break;
        case SDLK_LEFT:
            break;
        case SDLK_RIGHT:
            break;
        case SDLK_UP:
            break;
        case SDLK_DOWN:
            break;
        case SDLK_SPACE:
            break;
        case SDLK_LSHIFT:
            break;
        }
    }
}
