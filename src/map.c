/* #include <SDL2/SDL.h> */
#include "../inc/maze.h"

/**
 * draw_map - Draws the map on the minimap
 * @instance: SDL_Instance structure containing window and renderer
 * @player: Pointer to Player struct containing player's position
 * @map: map_t struct containing map layout
 */
void draw_map(SDL_Instance instance, Player *player, map_t map)
{
	SDL_Rect rect;
	int i, j;

	rect.x = 1;
	rect.y = 1;
	rect.w = MINIMAPW / map.cols;
	rect.h = MINIMAPH / map.rows;

	for (i = 0; i < map.rows; i++)
	{
		for (j = 0; j < map.cols; j++)
		{
			if (map.layout[i][j] == 0)
				set_color(&instance, "black");
			else if (map.layout[i][j] == 5)
				set_color(&instance, "blue");
			else
				set_color(&instance, "white");

			SDL_RenderFillRect(instance.renderer, &rect);
			rect.x += rect.w;
		}
		rect.x = 1;
		rect.y += rect.h;
	}

	draw_player(instance, player, MINIMAPW / map.cols, MINIMAPH / map.rows);
}

/**
 * draw_player - Draws the player on the minimap
 * @instance: SDL_Instance structure containing window and renderer
 * @player: Pointer to Player struct containing player's position
 * @width_ratio: Width ratio for scaling player position
 * @height_ratio: Height ratio for scaling player position
 */
void draw_player(SDL_Instance instance, Player *player, int width_ratio, int height_ratio)
{
	SDL_FRect rect_p;
	float x1, y1, x0, y0;

	x0 = player->x / BOXSIZE * width_ratio;
	y0 = player->y / BOXSIZE * height_ratio;
	x1 = 20 * cos(player->angle) + x0;
	y1 = 20 * sin(player->angle) + y0;

	rect_p.w = 8;
	rect_p.h = 8;
	rect_p.x = x0 - (rect_p.w / 2);
	rect_p.y = y0 - (rect_p.w / 2);

	set_color(&instance, "red");
	SDL_RenderFillRectF(instance.renderer, &rect_p);
	SDL_RenderDrawLineF(instance.renderer, x0, y0, x1, y1);
}

/**
 * raycasting - Performs raycasting to render the 3D scene
 * @instance: SDL_Instance structure containing window and renderer
 * @player: Pointer to Player struct containing player's position
 * @map: map_t struct containing map layout
 */
void raycasting(SDL_Instance instance, Player *player, map_t map)
{
	float length, tmp = player->angle;
	float i, line_height;
	int j = 0;

	for (i = -player->FOV / 2; i <= player->FOV / 2; i += player->FOV / SCREENWIDTH)
	{
		j += 1;
		player->angle = tmp + i;
		length = calc_impact(instance, player, map);
		line_height = SCREENHEIGHT / ((length * cos(i)) / BOXSIZE);
		draw_line(instance, line_height, j);
	}
	player->angle = tmp;
}

/**
 * draw_line - Draws a single vertical line on the screen
 * @instance: SDL_Instance structure containing window and renderer
 * @l_height: Height of the line to draw
 * @lineX: X-coordinate of the line on the screen
 */
void draw_line(SDL_Instance instance, double l_height, int lineX)
{
	float start, end;

	start = -l_height / 2 + SCREENHEIGHT / 2;
	end = l_height / 2 + SCREENHEIGHT / 2;

	if (start < 0)
		start = 0;
	if (end >= SCREENHEIGHT)
		end = SCREENHEIGHT - 1;

	SDL_RenderDrawLineF(instance.renderer, lineX, start, lineX, end);
	set_color(&instance, "blue");
	SDL_RenderDrawLineF(instance.renderer, lineX, 0, lineX, start);
	set_color(&instance, "reddish");
	SDL_RenderDrawLineF(instance.renderer, lineX, end, lineX, SCREENHEIGHT);
}
