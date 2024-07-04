#include "../inc/maze.h"

void draw_gun(SDL_Instance *instance)
{
	SDL_Rect weapon = {700, 450, 700, 450};
	SDL_Surface *surf;

	if(!instance->bmp)
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
	SDL_RenderCopy(instance->renderer, instance->bmp, NULL, &weapon);
}

void load_image(SDL_Instance *instance, char *filename)
{
	SDL_Rect font = {10, 10, SCREENWIDTH - 10, SCREENHEIGHT - 10};
	SDL_Surface *surf;

	if(!instance->bmp)
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
	SDL_RenderCopy(instance->renderer, instance->bmp, NULL, &font);
}
