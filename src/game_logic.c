#include "game_logic.h"
#include "constants.h"
#include "SDL2/SDL.h"
#include <math.h>
#include <stdio.h>
#include "player.h"

extern double posX, posY, dirX, dirY, planeX, planeY, moveSpeed, rotSpeed;
extern int worldMap[mapWidth][mapHeight];
int specialEventActive = 0;

// Define the external variables
int playerMapX;
int playerMapY;
SDL_Rect playerRect;

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
	// Update player position based on input or other game logic
	// ...
	
	// posX += playerMovementX * moveSpeed;
	// posY += playerMovementY * moveSpeed;

	// Clamp the player's position within the map boundaries
	int playerMapX = (int)floor(posX);
	int playerMapY = (int)floor(posY);

	// Clamp to map boundaries
	if (playerMapX < 0) playerMapX = 0;
	if (playerMapY < 0) playerMapY = 0;
	if (playerMapX >= MAP_WIDTH) playerMapX = MAP_WIDTH - 1;
	if (playerMapY >= MAP_HEIGHT) playerMapY = MAP_HEIGHT - 1;

	// Update player rectangle position
	SDL_Rect playerRect;
	playerRect.x = playerMapX * TILE_WIDTH;
	playerRect.y = playerMapY * TILE_HEIGHT;
	playerRect.w = TEXTURE_WIDTH;  // Assuming texture width
	playerRect.h = TEXTURE_HEIGHT; // Assuming texture height

	// Debugging output
	printf("posX: %f, posY: %f\n", posX, posY);
	printf("playerMapX: %d, playerMapY: %d\n", playerMapX, playerMapY);
	printf("playerMapX after clamping: %d, playerMapY after clamping: %d\n", playerMapX, playerMapY);
	printf("Player rect: x=%d, y=%d, w=%d, h=%d\n", playerRect.x, playerRect.y, playerRect.w, playerRect.h);

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

