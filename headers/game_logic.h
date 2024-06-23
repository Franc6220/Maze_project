#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "init.h"


void update_game(SDL_Instance instance);
void handle_input();
void update_player_position();
void handle_collisions();
void triggerSpecialEvent();
void endSpecialEvent();


#endif

