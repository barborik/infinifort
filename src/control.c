#include "includes.h"

Vector3f moveDelta;

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
            moveDelta.z =  0.0006f;
            break;
        case SDLK_s:
            moveDelta.z = -0.0006f;
            break;
        case SDLK_a:
            moveDelta.x =  0.0006f;
            break;
        case SDLK_d:
            moveDelta.x = -0.0006f;
            break;
        }
        break;
    case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            if (moveDelta.z > 0) moveDelta.z = 0;
            break;
        case SDLK_s:
            if (moveDelta.z < 0) moveDelta.z = 0;
            break;
        case SDLK_a:
            if (moveDelta.x > 0) moveDelta.x = 0;
            break;
        case SDLK_d:
            if (moveDelta.x < 0) moveDelta.x = 0;
            break;
        }
        break;
    }
}
