#include "../inc/maze.h"

/**
 * init_map - Initializes the map data structure by handling file operations
 * @file: Name of the file containing map data
 * Return: map_t data structure containing map information
 */
map_t init_map(char *file)
{
	FILE *fp = NULL;
	map_t map;

	// Open the file
	fp = open_file(file);

	// Read map data from file
	map = read_file(fp);

	// Close the file
	close_file(fp);

	return map;
}

/**
 * open_file - Opens a file with the given name for reading
 * @fname: Name of the file to open
 * Return: Pointer to the opened file stream
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

	return file;
}

/**
 * read_file - Reads map data from an open file stream and initializes the map structure
 * @file: Pointer to the open file stream
 * Return: Initialized map_t data structure containing map information
 */
map_t read_file(FILE *file)
{
	size_t count = 0;
	char *col = NULL;
	map_t *map;
	unsigned int i = 0, j;

	// Allocate memory for the map structure
	map = malloc(sizeof(map_t));

	// Calculate number of rows in the map
	map->rows = row_count(file) - 1;

	// Allocate memory for rows in map layout
	map->layout = malloc(sizeof(int *) * (map->rows + 1));

	// Read each line (row) from the file
	for (i = 0; i < map->rows; i++)
	{
		if (getline(&col, &count, file) == -1)
			break;
        
        // Calculate number of columns in the current row
        map->cols = strlen(col) - 1;

		// Allocate memory for columns in current row of map layout
		map->layout[i] = malloc(sizeof(int) * (strlen(col)));

		// Populate map layout with integer values from the file (convert char to int)
		for (j = 0; j < strlen(col) - 1; j++)
		{
			map->layout[i][j] = col[j] - '0';
		}
	}

	// Free allocated memory for temporary column buffer
	free(col);

	return *map;
}

/**
 * close_file - Closes the given file stream
 * @file: Pointer to the file stream to close
 */
void close_file(FILE *file)
{
	if (file)
		fclose(file);
}

/**
 * row_count - Counts the number of rows in a file stream
 * @file: Pointer to the file stream
 * Return: Number of rows (lines) in the file
 */
int row_count(FILE *file)
{
	char c;
	int line_count = 0;

	// Count lines until end of file (EOF)
	while (!feof(file))
	{
		c = fgetc(file);
		if (c == '\n')
		{
			line_count++;
		}
	}

	// Reset file position to the beginning
	fseek(file, 0, SEEK_SET);

	// Return total line count
	return line_count + 1;
}
