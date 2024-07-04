#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define MINIMAPW 200
#define MINIMAPH 200
#define SCREENWIDTH 1400
#define SCREENHEIGHT 720
#define BOXSIZE 32 /*how big a case in the map is in pixel*/
#define PI 3.14159265

/**
 * struct SDL_Instance - instance of SDL window and renderer
 * @window: The window object
 * @renderer: the renderer object
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *bmp;
} SDL_Instance;

/**
 * struct Player - instance of a player
 * @x: the x on map
 * @y: the y on map
 * @dirX: x facing coord
 * @dirY: y facing coord
 */

typedef struct Player
{
	float x;
	float y;
	float angle;
	float FOV;
} Player;


typedef struct map_t
{
	int rows;
	int cols;
	int **layout;
} map_t;


typedef struct status_t
{
	int minimap;
	int weapon;
	int level;
	int new_lvl;
	int quit;
	double time;
	double oldTime;
} status_t;

typedef struct color
{
	char *name;
	int RGB[4];
} color_t;

float len_calc(float x_value, float y_value);
float calc_impact(SDL_Instance inst, Player *player, map_t map);
float row_impact(Player *player, map_t map);
float col_impact(Player *player, map_t map);


void search_collision_x(Player *player, map_t map, float paceX);
void search_collision_y(Player *player, map_t map, float paceY);
double search_fps(status_t *status);

void poll_events(Player *player, map_t map, status_t *status);

void draw_map(SDL_Instance instance, Player *player, map_t map);

int init_instance(SDL_Instance *instance);
void init_player(Player *player, float X, float Y, float angle, float FOV);
map_t init_map(char *filename);

void close_file(FILE *fp);
FILE *open_file(char *filename);
map_t read_file(FILE *fp);
int row_count(FILE *file);

void draw_player(SDL_Instance instance, Player *player, int width_ratio, int height_ratio);
void raycasting(SDL_Instance instance, Player *player, map_t map);
void set_color(SDL_Instance *instance, char *color);

void draw_gun(SDL_Instance *instance);
void draw_line(SDL_Instance instance, double l_height, int lineX);
void load_image(SDL_Instance *instance, char *filename);
void exit_game(Player *player, status_t *status, map_t map);
#endif
