#include "game_logic.h"
#include "constants.h"
#include "SDL2/SDL.h"

extern double posX, posY, dirX, dirY, planeX, planeY, moveSpeed, rotSpeed;
extern int worldMap[mapWidth][mapHeight];
int specialEventActive = 0;

void handle_input()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_W])
	{
		if (worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == 0) posX += dirX * moveSpeed;
		if (worldMap[(int)posX][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
	}

	if (state[SDL_SCANCODE_S])
	{
		if (worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == 0) posX -= dirX * moveSpeed;
		if (worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
	}

	if (state[SDL_SCANCODE_A])
	{
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}

	if (state[SDL_SCANCODE_D])
	{
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
}

void update_player_position()
{
	// Additional position updates if necessary
}

void handle_collisions()
{
	// Additional collision handling logic if needed
}

void update_game(SDL_Instance instance)
{
	(void)instance; // Mark instance as unused

	// Add your game update logic here
	handle_input();
	update_player_position();
	handle_collisions();
}

