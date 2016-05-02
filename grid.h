#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "cell.h"

/** @brief Initalizes grid with 0 values.
 *
 * Takes in two dimensional grid, with it's desired constraint values and
 * allocates it to those values. Each cell is set to 0, representing death.
 * If allocation of the array fails, error value is returned. This function is
 * intended to be used when modifying array size is necessary. However all
 * existing values in parameter array, are lost in reallocation.
 *
 * @param x   desired amount of columns in the array.
 * @param y   desired amount of rows in the array.
 * @return pointer to  created two-dimensional array
 */
int **grid_new( int rows, int cols );

/** @brief Free dynamically allocated array.
 *
 */
void grid_free( int rows, int **arr);

/** @brief Initialize random values to each cell in a grid
 *
 * Initializes two dimensional array with random values, random meaning 1 or 0.
 * For convenience, this function takes limits of the array as integer values.
 * It doesn't check those values for now, so applying greater values will
 * end in segfault. Safety checks may be added later, but this may mean that
 * whole function must be refactored since it may be same to get x and y
 * constraints instead of making safety checks. So for now, make sure that all
 * given values match the actual size of the array. Also array will not be
 * resized in this function, you must do it before this.
 *
 * @param x   amount of columns in the array.
 * @param y   amount of rows in the array.
 * @param arr array to be initalized.
 */
void grid_rand( int rows, int cols, int **arr );

/** @brief Update grid to next values.
 *
 * Given two dimensional grid is updated to next state, using current states
 * of each "cell" and given rules to apply. Previous values in the grid are
 * deleted and therefore lost, so don't use this to "peek" next values, with an
 * array that you don't want to update. Rules are given as integer arrays. Each
 * item in array represents number of neighbours that gives or retains life for
 * the cell.
 *
 * @param x   Amount of columns in the array.
 * @param y   Amount of rows in the array.
 * @param arr array to be initalized.
 * @param live_a rules to apply when cell is currently alive.
 * @param live_d rules to apply when cell is currently dead.
 */
void grid_next( int x, int y, int **grid, int *live_a, int live_s, int *live_d, int dead_s );

/** @brief Update grid to previous values.
 *
 * @param x   Amount of columns in the array.
 * @param y   Amount of rows in the array.
 * @param arr Array to update.
 */
void grid_prev( int x, int y, int **arr, int *live_a, int *live_d );

/** @brief Print two dimensional array to console.
 *
 */
void grid_print( int x, int y, int **arr );

/** @brief Count current neighbours for a cell.
 *
 * Each cell in the grid has 0-8 neighbours. This function calculates those
 * neighbours using current x and y location of the cell. This is usefull since
 * it is often necessary to know how many neighbours certain cell has, for
 * example to predict their future state. This function doesn't have safety
 * checks for x and y, so make sure they are within maximum limits.
 *
 * @param x Column of the cell.
 * @param y Row of the cell.
 * @max_x   Number of columns in the grid-
 * @max_y   Number of rows in the grid.
 * @grid    Grid containing the cell that is examined.
 * @return  Count of neighbours for the given cell.
 */
int grid_nbrs( int x, int y, int max_x, int max_y, int **grid );


#endif /* GRID_H_ */
