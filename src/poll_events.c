/* #include <SDL2/SDL.h> */
/* #include <math.h> */
#include "../inc/maze.h"

/**
 * poll_events - Handles SDL events for player input
 * @player: Pointer to Player struct containing player's position and angle
 * @map: map_t struct containing map layout
 * @status: Pointer to status_t struct containing game status
 *
 * This function polls SDL events such as key presses and updates the player's
 * position and angle accordingly. It also handles game-specific actions like
 * quitting the game, changing levels, toggling the minimap, and managing weapon display.
 */
void poll_events(Player *player, map_t map, status_t *status)
{
	SDL_Event event;
	SDL_KeyboardEvent key;
	float paceX = 0, paceY = 0;
	double mvSpeed, rotSpeed;
	double f_time = search_fps(status);

	mvSpeed = f_time * 200;
	rotSpeed = f_time * 2.5;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			status->quit = 1;
			break;
		case SDL_KEYDOWN:
			key = event.key;
			switch (key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				status->quit = 1;
				break;
			case SDL_SCANCODE_W:
				paceX = mvSpeed * cos(player->angle);
				paceY = mvSpeed * sin(player->angle);
				break;
			case SDL_SCANCODE_S:
				paceX = mvSpeed * cos(player->angle - PI);
				paceY = mvSpeed * sin(player->angle - PI);
				break;
			case SDL_SCANCODE_A:
				paceX = mvSpeed * cos(player->angle - PI / 2);
				paceY = mvSpeed * sin(player->angle - PI / 2);
				break;
			case SDL_SCANCODE_D:
				paceX = mvSpeed * cos(player->angle + PI / 2);
				paceY = mvSpeed * sin(player->angle + PI / 2);
				break;
			case SDL_SCANCODE_RETURN:
				status->new_lvl = 1;
				status->level += 1;
				break;
			case SDL_SCANCODE_LEFT:
				player->angle -= rotSpeed;
				break;
			case SDL_SCANCODE_RIGHT:
				player->angle += rotSpeed;
				break;
			case SDL_SCANCODE_P:
				if (status->minimap == 0)
					status->minimap = 1;
				else
					status->minimap = 0;
				break;
			case SDL_SCANCODE_Z:
				if (status->weapon == 0)
					status->weapon = 1;
				else
					status->weapon = 0;
				break;
			case SDL_SCANCODE_UNKNOWN:
				// Handle unknown scancode if necessary
				break;
			default:
				break;
			}
			search_collision_x(player, map, paceX);
			search_collision_y(player, map, paceY);
			break;
		}
	}
}

/**
 * search_collision_x - Checks collision in the x-direction
 * @player: Pointer to Player struct containing player's position
 * @map: map_t struct containing map layout
 * @paceX: Movement pace in the x-direction
 *
 * This function checks if the player collides with walls in the x-direction
 * and adjusts the player's position accordingly.
 */
void search_collision_x(Player *player, map_t map, float paceX)
{
	int row, col, collide;
	float x1, tmp;

	tmp = player->x;
	x1 = player->x + paceX;
	row = player->y / BOXSIZE;
	col = x1 / BOXSIZE;
	collide = 0;

	if (map.layout[row][col] != 0 && map.layout[row][col - 1] == 5)
	{
		collide = 1;
		player->x = tmp - paceX;
	}

	if (collide == 0)
	{
		player->x = tmp + paceX;
	}
}

/**
 * search_collision_y - Checks collision in the y-direction
 * @player: Pointer to Player struct containing player's position
 * @map: map_t struct containing map layout
 * @paceY: Movement pace in the y-direction
 *
 * This function checks if the player collides with walls in the y-direction
 * and adjusts the player's position accordingly.
 */
void search_collision_y(Player *player, map_t map, float paceY)
{
	int row, col, collide;
	float y1, tmp;

	tmp = player->y;
	y1 = player->y + paceY;
	row = y1 / BOXSIZE;
	col = player->x / BOXSIZE;
	collide = 0;

	if (map.layout[row][col] != 0 && map.layout[row][col - 1] == 5)
	{
		collide = 1;
		player->y = tmp - paceY;
	}

	if (collide == 0)
	{
		player->y = tmp + paceY;
	}
}

/**
 * search_fps - Calculates the frame per second (FPS)
 * @status: Pointer to status_t struct containing timing information
 * 
 * This function calculates the FPS based on the difference between
 * current and previous time.
 *
 * Return: The time difference in seconds (fps)
 */
double search_fps(status_t *status)
{
	double f_time;
	
	status->oldTime = status->time;
    status->time = SDL_GetTicks();
    f_time = (status->time - status->oldTime) / 1000.0;
	return (f_time);
}
