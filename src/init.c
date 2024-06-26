#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "init.h"
#include "textures.h"
#include "constants.h"

int init_instance(SDL_Instance *instance)
{
	// Initialize SDL video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}

	// Initialize SDL_image for PNG loading
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		fprintf(stderr, "Unable to initialize IMG: %s\n", IMG_GetError());
		return (0);
	}

	// Create SDL window
	instance->window = SDL_CreateWindow("SDL2 \\0/", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	// Create SDL renderer
	instance->renderer = SDL_CreateRenderer(instance->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	return (0);
}


// Initialize the game
int initialize_game(SDL_Instance* instance)
{
	if (init_instance(instance) != 0)
		return 0;

	if (!load_textures(instance->renderer))
	{
		SDL_DestroyRenderer(instance->renderer);
		SDL_DestroyWindow(instance->window);
		SDL_Quit();
		return 0;
	}

	// Additional game initialization logic goes here
	

	return 1;
}

