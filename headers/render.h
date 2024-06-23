#ifndef RENDER_H
#define RENDER_H

#include "init.h"

void render_ui(SDL_Instance instance);
void render_hud(SDL_Instance instance);
void render_special_effects(SDL_Instance instance);
void draw_scene(SDL_Instance instance);
void draw_map(SDL_Instance instance);
void render_game(SDL_Instance instance);

#endif
