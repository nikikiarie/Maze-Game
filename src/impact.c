#include "../inc/maze.h"

/**
 * calc_impact - Calculates the impact length and sets color based on collision type
 * @inst: SDL_Instance pointer for rendering
 * @player: Pointer to Player struct containing player's position and angle
 * @map: map_t struct containing map layout
 * Return: Length of impact
 */
float calc_impact(SDL_Instance inst, Player *player, map_t map)
{
	float len_real, len0, len1;

	len0 = row_impact(player, map);
	len1 = col_impact(player, map);

	// Determine which impact length is smaller and set color accordingly
	if (len0 < len1)
	{
		len_real = len0;
		set_color(&inst, "dark purple");
	}
	else
	{
		len_real = len1;
		set_color(&inst, "light blue");
	}

	return len_real;
}

/**
 * len_calc - Calculates the length of a vector
 * @x_value: x component of the vector
 * @y_value: y component of the vector
 * Return: Length of the vector
 */
float len_calc(float x_value, float y_value)
{
	x_value *= x_value;
	y_value *= y_value;
	return sqrt(x_value + y_value);
}

/**
 * row_impact - Calculates impact length for rows in map
 * @player: Pointer to Player struct containing player's position and angle
 * @map: map_t struct containing map layout
 * Return: Impact length for rows
 */
float row_impact(Player *player, map_t map)
{
	int i, collide, mapY, row, col;
	double x0, y0, x1, y1;

	x0 = player->x, y0 = player->y;
	mapY = player->y / BOXSIZE;
	collide = 0;
	i = 0;

	while (collide == 0)
	{
		if (sin(player->angle) >= 0)
		{
			y1 = (mapY + 1 + i) * BOXSIZE;
			x1 = fabs(y1 - y0) / tan(player->angle) + x0;
			row = y1 / BOXSIZE, col = x1 / BOXSIZE;

			if (row < 0 || row >= map.rows || col < 0 || col >= map.cols)
				collide = 1;
			if (map.layout[row][col] != 0 && map.layout[row][col] != 5)
				collide = 1;
		}
		else
		{
			y1 = (mapY - i) * BOXSIZE;
			x1 = -fabs(y1 - y0) / tan(player->angle) + x0;
			row = y1 / BOXSIZE, col = x1 / BOXSIZE;

			if (row < 0 || row >= map.rows || col < 0 || col >= map.cols)
				collide = 1;
			else if (map.layout[row - 1][col] != 0 && map.layout[row - 1][col] != 5)
				collide = 1;
		}
		i++;
	}

	return len_calc(x0 - x1, y0 - y1);
}

/**
 * col_impact - Calculates impact length for columns in map
 * @player: Pointer to Player struct containing player's position and angle
 * @map: map_t struct containing map layout
 * Return: Impact length for columns
 */
float col_impact(Player *player, map_t map)
{
	int i, collide, mapX, row, col;
	double x0, y0, x1, y1;

	x0 = player->x, y0 = player->y;
	mapX = player->x / BOXSIZE;
	collide = 0;
	i = 0;

	while (collide == 0)
	{
		if (cos(player->angle) >= 0)
		{
			x1 = (mapX + 1 + i) * BOXSIZE;
			y1 = (x1 - x0) * tan(player->angle) + y0;
			row = y1 / BOXSIZE, col = x1 / BOXSIZE;

			if (row < 0 || row >= map.rows || col < 0 || col >= map.cols)
				collide = 1;
			else if (map.layout[row][col] != 0 && map.layout[row][col] != 5)
				collide = 1;
		}
		else
		{
			x1 = (mapX - i) * BOXSIZE;
			y1 = (x1 - x0) * tan(player->angle) + y0;
			row = y1 / BOXSIZE, col = x1 / BOXSIZE;

			if (row < 0 || row >= map.rows || col < 0 || col >= map.cols)
				collide = 1;
			else if (map.layout[row][col - 1] != 0 && map.layout[row][col - 1] != 5)
				collide = 1;
		}
		i++;
	}

	return len_calc(x0 - x1, y0 - y1);
}
