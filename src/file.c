#include "../inc/maze.h"


/**
 * handle_file - calls all file handling functions
 * @filename: string pointer to file name
 * Return: map_t datastructure of map information
 */
map_t init_map(char *file)
{
	FILE *fp = NULL;
	map_t map;

	fp = open_file(file);
	map = read_file(fp);
	close_file(fp);

	return (map);
}

/**
 * open_file - opens a file
 * @fname: string pointer
 * Return: pointer
 */
FILE *open_file(char *fname)
{
	FILE *file = NULL;

	file = fopen(fname, "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", fname);
		exit(EXIT_FAILURE);
	}

	return (file);
}

/**
 * read_file - reads file content
 * @file: pointer to file
 * Return: map data
 */
map_t read_file(FILE *file)
{
	size_t count = 0;
	char *col = NULL;
	map_t *map;
	unsigned int i = 0, j;


	map = malloc(sizeof(map_t));
	map->rows = row_count(file) - 1;
	map->layout = malloc(sizeof(int *) * (map->rows + 1));

	for (i = 0; i < map->rows; i++)
	{
		 if (getline(&col, &count, file) == -1)
		 	break;
        map->cols = strlen(col) - 1;
		map->layout[i] = malloc(sizeof(int) * (strlen(col)));
		for (j = 0; j < strlen(col) - 1; j++)
		{
			map->layout[i][j] = col[j] - '0';
		}
	}
	free(col);

	return (*map);
}
void close_file(FILE *file)
{
	if (file)
		fclose(file);
}

int row_count(FILE *file)
{
	char c;
	int l_count = 0;

	while (!feof(file))
	{
		c = fgetc(file);
		if (c == '\n')
		{
			l_count++;
		}
	}

	fseek(file, 0, SEEK_SET);

	return (l_count + 1);
}
