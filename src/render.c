#include <SDL2/SDL.h>
#include "render.h"
#include "constants.h"


extern SDL_Texture* wallTextures[4];
extern double posX, posY, dirX, dirY, planeX, planeY;
extern int specialEventActive;

void render_ui(SDL_Instance instance)
{
	SDL_Rect healthBar = {10, 10, 100, 20};
	SDL_SetRenderDrawColor(instance.renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(instance.renderer, &healthBar);
}

void render_hud(SDL_Instance instance)
{
	SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255);
	int centerX = screenWidth / 2;
	int centerY = screenHeight / 2;
	SDL_RenderDrawLine(instance.renderer, centerX - 10, centerY, centerX + 10, centerY);
	SDL_RenderDrawLine(instance.renderer, centerX, centerY - 10, centerX, centerY + 10);
}

void render_special_effects(SDL_Instance instance)
{
	if (specialEventActive)
	{
		// Render sunset background
		SDL_SetRenderDrawColor(instance.renderer, 255, 102, 0, 255); // Orange
		SDL_Rect sunsetRect = {0, 0, screenWidth, screenHeight};
		SDL_RenderFillRect(instance.renderer, &sunsetRect);
	}
}

void triggerSpecialEvent()
{
	specialEventActive = 1; // Set to 1 when special event starts
}

void endSpecialEvent()
{
	specialEventActive = 0; // Set to 0 when special event ends
	
}


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
		
		if (wallTextures[texNum] != NULL) // Check if texture is available
		{
			SDL_RenderCopy(instance.renderer, wallTextures[texNum], &srcRect, &wallRect);
		}
		else
		{
			SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255); // Set color to white
			SDL_RenderFillRect(instance.renderer, &wallRect);
		}

	}
}

void draw_map(SDL_Instance instance)
{
	int mapDisplayWidth = screenWidth / 4;  // Example: display the map in a quarter of the screen width
	int mapDisplayHeight = screenHeight / 4; // Example: display the map in a quarter of the screen height
	
	
       	// Position offset for the map (e.g., top-left corner)
	int offsetX = screenWidth - mapDisplayWidth; // Adjust as needed
	int offsetY = 0;


	SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255);          // Set color for map
	for (int i = 0; i < mapWidth; i++)
	{
		for (int j = 0; j < mapHeight; j++)
		{
			if (worldMap[i][j] != 0)
			{
				SDL_Rect mapRect = {offsetX + i * (mapDisplayWidth / mapWidth), offsetY + j * (mapDisplayHeight / mapHeight), mapDisplayWidth / mapWidth, mapDisplayHeight / mapHeight};      // Scale map coordinates for display
				SDL_RenderFillRect(instance.renderer, &mapRect); // Render map block
			}
		}
	}
}

void render_game(SDL_Instance instance)
{
	// Clear the renderer with a neutral color
	SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 255);
	SDL_RenderClear(instance.renderer);

	// Set color for the ceiling
	SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 255);
	SDL_Rect ceilingRect = {0, 0, screenWidth, screenHeight / 2};
	SDL_RenderFillRect(instance.renderer, &ceilingRect);

	// Set color for the floor
	SDL_SetRenderDrawColor(instance.renderer, 255, 140, 0, 255); // Darker orange for the floor
	SDL_Rect floorRect = {0, screenHeight / 2, screenWidth, screenHeight / 2};
	SDL_RenderFillRect(instance.renderer, &floorRect);

	draw_scene(instance);
	draw_map(instance);
	render_ui(instance);
	render_hud(instance);
	render_special_effects(instance);

	SDL_RenderPresent(instance.renderer);
}
