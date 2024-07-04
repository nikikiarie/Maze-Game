#include "../inc/maze.h"

/**
 * init_instance - initialize an SDL instance and checks for error
 * @instance: an instance that hold the address of the window and render
 * Return: 0 on success
 * Or 1 on error
 */
int init_instance(SDL_Instance *instance)
{
	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Error: %s/n",
			SDL_GetError());
		return (1);
	}
	/* Create a new Window instance */
	instance->window = SDL_CreateWindow("The Maze Game", SDL_WINDOWPOS_CENTERED,
					    SDL_WINDOWPOS_CENTERED,
					    SCREENWIDTH, SCREENHEIGHT, 0);
	if (instance->window == NULL)
	{
		fprintf(stderr, "Error: %s\n",
			SDL_GetError());
		SDL_Quit();
		return (1);
	}
	/* Create a new renderer instance linked to the Window */
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
						SDL_RENDERER_ACCELERATED |
						SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "Error: %s\n",
			SDL_GetError());
		SDL_Quit();
		return (1);
	}
    instance->bmp = NULL;
	return (0);
}

/**
 * init_player - initialize a player
 * @player: an instance of the player
 *
 * Return: Nothing
 */
void init_player(Player *player, float x_value, float y_value, float angle, float FOV)
{
	player->x= (x_value - 0.5) * BOXSIZE;
	player->y = (y_value - 0.5) * BOXSIZE;
	player->angle = angle;
	player->FOV = FOV;
}

void set_color(SDL_Instance *instance, char *color)
{
	int i = 0;
	color_t colors[] = {
		{"red", {255, 17, 17, 255}},
		{"blue", {153, 204, 255, 255}},
		{"light blue", {13,27,42, 255}},
		{"green", {0, 204, 0, 255}},
		{"reddish", {36, 33, 33,255}},
		{"yellow", {255, 255, 0, 255}},
		{"grey", {128, 128, 128, 255}},
		{"purple", {13,27,42}},
		{"white", {255, 255, 255, 255}},
		{"purple", {127, 0, 255, 255}},
		{"dark purple", {27, 56, 87, 255}},
        {"brown", {90, 19, 19, 255}},
		{"black", {0, 0, 0, 255}},
		{NULL, {0, 0, 0, 255}}
		};

	while (colors[i].name)
	{
		if (strcmp(color, colors[i].name) == 0)
		{
			break;
		}
		i++;
	}
	SDL_SetRenderDrawColor(instance->renderer, colors[i].RGB[0], 
	colors[i].RGB[1], colors[i].RGB[2], colors[i].RGB[3]);
}

