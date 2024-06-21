#include <SDL2/SDL.h>
#include "render.h"
#include "constants.h"


extern SDL_Texture* wallTextures[4];

void draw_scene(SDL_Instance instance)
{
	for (int x = 0; x < screenWidth; x++)
	{
		double cameraX = 2 * x / (double)screenWidth - 1;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		int mapX = (int)posX;
		int mapY = (int)posY;

		double sideDistX, sideDistY;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX, stepY;
		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0  - posY) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}

		if (side == 0)
		{
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		}
		else
		{
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
		}


		int lineHeight = (int)(screenHeight / perpWallDist);
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0) 
		{
			drawStart = 0;
		}
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
		{
			drawEnd = screenHeight - 1;
		}


		SDL_Rect wallRect = {x, drawStart, 1, drawEnd - drawStart};

		int texNum = worldMap[mapX][mapY] - 1;
		
		// Calculate texture offset
		double wallX; // Exact position of where wall was hit
		if (side == 0)
		{
			wallX = posY + perpWallDist * rayDirY;
		}
		else
		{
			wallX = posX + perpWallDist * rayDirX;
		}
		wallX -= floor(wallX);

		// Texture coordinates
		int texX = (int)(wallX * (double)TEXTURE_WIDTH);
		if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
		{
			texX = TEXTURE_WIDTH - texX - 1;
		}

		// Draw the wall slice
		SDL_Rect srcRect = { texX, 0, 1, TEXTURE_HEIGHT };

		SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255); // Set color to white
		SDL_RenderFillRect(instance.renderer, &wallRect);

		SDL_RenderCopy(instance.renderer, wallTextures[texNum], &srcRect, &wallRect);
	}
}

void draw_map(SDL_Instance instance)
{
	SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255);          // Set color for map
	for (int i = 0; i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
		{
			if (worldMap[i][j] != 0)
			{
				SDL_Rect mapRect = {i * 10, j *10, 10, 10};      // Scale map coordinates for display
				SDL_RenderFillRect(instance.renderer, &mapRect); // Render map block
			}
		}
	}
}
