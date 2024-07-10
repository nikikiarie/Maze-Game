/* #include <SDL2/SDL.h> */
#include "../inc/maze.h"

/**
 * main - Entry point of the program
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	SDL_Instance instance;
	Player player;
	status_t status = {0, 0, 0, 0, 0, 0, 0};
	SDL_bool minimap = SDL_TRUE;
	map_t map;

	if (init_instance(&instance) != 0)
		return 1;

	while (!status.quit)
	{
		map = init_map("maps/map");
		init_player(&player, map.cols - 1, map.rows - 1, -PI / 2, PI / 3); 
		/* The coordinates given are those in the map */

		while (!status.quit && !status.new_lvl)
		{
			set_color(&instance, "white");
			SDL_RenderClear(instance.renderer);
			poll_events(&player, map, &status);
			switch (status.level)
			{
				case 0:
					load_image(&instance, "images/enter.bmp");
					break;
				case 1:
					instance.bmp = NULL;
					raycasting(instance, &player, map);
					if (status.minimap != 0)
					{
						draw_map(instance, &player, map);
					}
					if (status.weapon != 0)
					{
						draw_gun(&instance);
					}
					exit_game(&player, &status, map);
					break;
				case 2:
					load_image(&instance, "images/end.bmp");
					break;
				case 3:
					status.quit = 1;
			}
			SDL_RenderPresent(instance.renderer);
		}
		status.new_lvl = 0;
	}

	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return 0;
}

/**
 * exit_game - Checks if the player is on an exit tile and increments level if true
 * @player: Pointer to Player struct containing player's position
 * @status: Pointer to status_t struct containing game status
 * @map: map_t struct containing map layout
 */
void exit_game(Player *player, status_t *status, map_t map)
{
	int row, col;

	row = player->x / BOXSIZE;
	col = player->y / BOXSIZE;
	if (map.layout[row][col] == 5)
		status->level += 1;
}
