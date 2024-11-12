#include "includes.h"

void Control(SDL_Event event, Camera *camera)
{
    switch (event.type)
    {
    case SDL_MOUSEMOTION:
        camera->yaw += 0.002f * event.motion.xrel;
        camera->pitch += 0.002f * event.motion.yrel;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            camera->position.x += 0.1f * cos(camera->pitch) * sin(camera->yaw);
            camera->position.y += 0.1f * -sin(camera->pitch);
            camera->position.z += 0.1f * cos(camera->pitch) * cos(camera->yaw);
            break;
        case SDLK_s:
            camera->position.x -= 0.1f * cos(camera->pitch) * sin(camera->yaw);
            camera->position.y -= 0.1f * -sin(camera->pitch);
            camera->position.z -= 0.1f * cos(camera->pitch) * cos(camera->yaw);
            break;
        case SDLK_a:
            camera->position.x -= 0.1f * sin(camera->yaw + M_PI / 2.0f);
            camera->position.z -= 0.1f * cos(camera->yaw + M_PI / 2.0f);
            break;
        case SDLK_d:
            camera->position.x += 0.1f * sin(camera->yaw + M_PI / 2.0f);
            camera->position.z += 0.1f * cos(camera->yaw + M_PI / 2.0f);
            break;
        case SDLK_LEFT:
            camera->yaw -= 0.1f;
            break;
        case SDLK_RIGHT:
            camera->yaw += 0.1f;
            break;
        case SDLK_UP:
            camera->pitch -= 0.1f;
            break;
        case SDLK_DOWN:
            camera->pitch += 0.1f;
            break;
        case SDLK_SPACE:
            camera->position.y += 0.1f;
            break;
        case SDLK_LSHIFT:
            camera->position.y -= 0.1f;
            break;
        }
    }
}
