#include <SDL2/SDL.h>
#include "events.h"
#include "init.h"
#include "constants.h"

void handle_key_press(SDL_Event event)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_UP:
					// Move forward in player Direct
					if (worldMap[(int)(posX + dirX * moveSpeed)][(int)posY] == 0) posX += dirX * moveSpeed;
					if (worldMap[(int)posX][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
					break;
				case SDLK_DOWN:
					// Move backward
					if (worldMap[(int)(posX - dirX * moveSpeed)][(int)posY] == 0) posX -= dirX * moveSpeed;
					if (worldMap[(int)posX][(int)(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
					break;
				case SDLK_LEFT:
					// Rotate left (counter-clockwise)
					// Use rotation matrix for both direction and camera plane
				{
					double oldDirX = dirX;
					dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
					dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
					double oldPlaneX = planeX;
					planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
					planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
				}
					break;
				case SDLK_RIGHT:
					// Rotate right (clockwise)
				{
					double oldDirX = dirX;
					dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
					dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
					double oldPlaneX = planeX;
					planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
					planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
				}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}


int poll_events()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				return (1);
			case SDL_KEYDOWN:
				handle_key_press(event);
				break;
			case SDL_WINDOWEVENT:
				// Handle window events (resize, focus, etc.)
				if (event.window.event == SDL_WINDOWEVENT_CLOSE)
					return 1; // Handle window close event
				break;
			default:
				break;

		}
	}
	return (0);   // Continue running the game
}
