#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// Define constants for the game
#define MINIMAPW 200
#define MINIMAPH 200
#define SCREENWIDTH 1400
#define SCREENHEIGHT 720
#define BOXSIZE 32 /* how big a case in the map is in pixel */
#define PI 3.14159265

/**
 * struct SDL_Instance - instance of SDL window and renderer
 * @window: The window object
 * @renderer: the renderer object
 * @bmp: texture object
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
 * @angle: player's facing angle
 * @FOV: player's field of view angle
 */
typedef struct Player
{
    float x;
    float y;
    float angle;
    float FOV;
} Player;

/**
 * struct map_t - structure for the game map
 * @rows: number of rows in the map
 * @cols: number of columns in the map
 * @layout: 2D array representing the map layout
 */
typedef struct map_t
{
    int rows;
    int cols;
    int **layout;
} map_t;

/**
 * struct status_t - game status information
 * @minimap: flag indicating minimap visibility
 * @weapon: current weapon selection
 * @level: current level
 * @new_lvl: flag indicating a new level
 * @quit: flag indicating game quit request
 * @time: current game time
 * @oldTime: previous game time
 */
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

/**
 * struct color_t - structure for defining colors
 * @name: name of the color
 * @RGB: array representing RGB color values
 */
typedef struct color_t
{
    char *name;
    int RGB[4];
} color_t;

// Function prototypes
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
