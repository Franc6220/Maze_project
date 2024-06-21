#ifndef INIT_H
#define INIT_H

typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *instance);

extern double posX, posY; // Example declarations
extern double dirX, dirY;
extern double moveSpeed;
extern double rotSpeed;
extern double planeX, planeY;

#endif
