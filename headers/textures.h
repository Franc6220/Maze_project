#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>

extern SDL_Texture* wallTextures[4];

int load_textures(SDL_Renderer* renderer);

#endif
