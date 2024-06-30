#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *instance);
int load_textures(SDL_Renderer *renderer);
int initialize_game(SDL_Instance* instance);
void draw_life(SDL_Instance instance, int offsetX, int offsetY);

extern double posX, posY; // Example declarations
extern double dirX, dirY;
extern double moveSpeed;
extern double rotSpeed;
extern double planeX, planeY;

#endif
