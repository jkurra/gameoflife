#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "cell.h"

/*
 * Initialize grid with 0 values
 */
int **grid_init(int x, int y, int **arr);

/*
 * Give random values to each cell in a grid
 */
int **grid_rand(int x, int y, int **arr);

/*
 * Calculate next state for the grid
 */
void grid_next(int x, int y, int **arr);

/*
 * Calculate next state for the grid
 */
void grid_prev(int x, int y, int **arr);

/*
 * Calculate next state for the grid
 */
int grid_nbrs_count(int x, int y, int max_x, int max_y, int **grid);


#endif
