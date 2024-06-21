#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "textures.h"

SDL_Texture* wallTextures[4];

int load_textures(SDL_Renderer* renderer)
{
	SDL_Surface *wallSurface = NULL;
	const char *textureFiles[4] = {"texture1.png", "texture2.png", "texture3.png", "texture4.png"};

	for (int i = 0; i < 4; i++)
	{
		char fullPath[256];
		snprintf(fullPath, sizeof(fullPath), "/home/samuel/textures/%s", textureFiles[i]);

		wallSurface = IMG_Load(fullPath);
		if (!wallSurface)
		{
			printf("Failed to load %s SDL_image Error: %s\n", textureFiles[i], IMG_GetError());
			return (0);
		}
		wallTextures[i] = SDL_CreateTextureFromSurface(renderer, wallSurface);
		if (!wallTextures[i])
		{
			printf("Failed to create texture from %s SDL Error: %s\n", textureFiles[i], SDL_GetError());
			SDL_FreeSurface(wallSurface);
			return (0);
		}

		SDL_FreeSurface(wallSurface);
	}
	return (1);
}
