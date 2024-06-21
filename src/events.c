#include <SDL2/SDL.h>
#include "events.h"
#include "init.h"

void handle_key_press(SDL_Event event)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_UP:
					// Move forward in player Direct
					posX += dirX * moveSpeed;
					posY += dirY * moveSpeed;
					break;
				case SDLK_DOWN:
					// Move backward
					posX -= dirX * moveSpeed;
					posY -= dirY * moveSpeed;
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
			default:
				break;

		}
	}
	return (0);
}
