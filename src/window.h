#ifndef __WINDOW_H_
#define __WINDOW_H_

#define WINDOW_TITLE "Infinifort"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

extern SDL_Window *window;
extern SDL_Renderer *renderer;

void CreateWindow(void);

#endif
