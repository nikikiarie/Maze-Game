#include "../inc/maze.h"

/**
 * draw_gun - Draws a gun image on the screen
 * @instance: Pointer to the SDL instance containing window, renderer, and texture
 */
void draw_gun(SDL_Instance *instance)
{
	SDL_Rect weapon = {700, 450, 700, 450}; // Define position and size of the weapon image
	SDL_Surface *surf;

	// Load the weapon image if not already loaded
	if (!instance->bmp)
	{
		surf = SDL_LoadBMP("images/weapon1.bmp");
		if (!surf)
		{
			printf("Error: %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		instance->bmp = SDL_CreateTextureFromSurface(instance->renderer, surf);
		SDL_FreeSurface(surf);
	}

	// Render the weapon image onto the screen
	SDL_RenderCopy(instance->renderer, instance->bmp, NULL, &weapon);
}

/**
 * load_image - Loads and renders an image onto the screen
 * @instance: Pointer to the SDL instance containing window, renderer, and texture
 * @filename: Name of the image file to load
 */
void load_image(SDL_Instance *instance, char *filename)
{
	SDL_Rect font = {10, 10, SCREENWIDTH - 10, SCREENHEIGHT - 10}; // Define position and size of the image
	SDL_Surface *surf;

	// Load the image if not already loaded
	if (!instance->bmp)
	{
		surf = SDL_LoadBMP(filename);
		if (!surf)
		{
			printf("Error: %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		instance->bmp = SDL_CreateTextureFromSurface(instance->renderer, surf);
		SDL_FreeSurface(surf);
	}

	// Render the image onto the screen
	SDL_RenderCopy(instance->renderer, instance->bmp, NULL, &font);
}
