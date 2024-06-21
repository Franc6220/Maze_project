#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "../headers/constants.h"
#include "../headers/init.h"
#include "../headers/textures.h"
#include "../headers/render.h"
#include "../headers/events.h"


int main(void)
{
	SDL_Instance instance;

	if (init_instance(&instance) != 0)
		return (1);
	/*
	 * C will always be awesome
	 * This is an infinite loop
	 */

	if (!load_textures(instance.renderer))
	{
		SDL_DestroyRenderer(instance.renderer);
		SDL_DestroyWindow(instance.window);
		SDL_Quit();
		return (1);
	}

	while (1)
	{
		SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 255);
		SDL_RenderClear(instance.renderer);
		
		if (poll_events() == 1)
			break;
		
		// Call scene and map rendering function
		draw_scene(instance);
		draw_map(instance);
		
		SDL_RenderPresent(instance.renderer);
	}

	for (int i = 0; i < 4; i++)
	{
		SDL_DestroyTexture(wallTextures[i]);
	}

	// Cleanup SDL
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}

