#ifndef __WINDOW_
#define __WINDOW_

#define WINDOW_TITLE "Infinifort"

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 300

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;
extern SDL_Surface *surface;

void CreateWindow(void);

#endif
