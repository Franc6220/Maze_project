#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "../headers/constants.h"
#include "../headers/init.h"
#include "../headers/textures.h"
#include "../headers/game_logic.h"
#include "../headers/render.h"
#include "../headers/events.h"
 #include "../headers/player.h"


int main (void)
{
	SDL_Instance instance;

	if (!initialize_game(&instance))
		return (1);


	while (1)
	{
		// Poll events, update game logic, render scene, map, HUD, etc.
		if (poll_events() == 1)
			break;
		
		update_game(instance); // Update game
		render_game(instance); // Render the game scene

		SDL_RenderPresent(instance.renderer); // Present rendered image
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

