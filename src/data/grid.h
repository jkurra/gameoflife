#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "cell.h"

/** @brief Structure for GameGrid object.
 *
 */
typedef struct
{
    /* Amount of rows and columns */
    int rows;
    int cols;

    /* Array Full grid filled with cells. */
    Cell ***g_grid;

    /* Array for CellsOfInterest */
    int coiCount;
    /* Array for CellsOfInterest */
    Cell **coiArray;

} Grid;

typedef struct
{
    /* Array for CellsOfInterest */
    Cell **coiArray;
    /* Array for CellsOfInterest */
    int coiCount;

} CellGrid;

/** @brief Initalizes grid with 0 values.
 *
 * Takes in desired constraint values of two dimensional grid and allocates new
 * grid with those values. Each cell is set to 0, representing death.
 * If allocation of the array fails, error value is returned. This function is
 * intended to be used when modifying array size is necessary. However all
 * existing values in parameter array, are lost in reallocation.
 *
 * @param x   Desired amount of columns in the array.
 * @param y   Desired amount of rows in the array.
 * @return pointer to  created two-dimensional array
 */
Grid *Grid_new( int rows, int cols );

/** @brief Frees given grid and all its member values.
 *
 *  TODO: Not yet implemented.
 */
void Grid_free( Grid *grid );

/** @brief Initalizes grid with 0 values.
 *
 *  TODO: Not yet implemented.
 */
void Grid_empty( Grid *grid );

/** @brief Resizes grid with given dimensions.
 *
 * Takes in two dimensional grid, with it's new desired constraint values and
 * allocates it to those values. Each new cell is set to 0, representing death.
 *
 * @param grid pointer to grid.
 * @param x   Desired amount of columns in the array.
 * @param y   Desired amount of rows in the array.
 * @return pointer to reallocated grid.
 */
void Grid_resize( Grid *grid, int new_rows, int new_cols );

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
void Grid_rand( Grid *grid );

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
void Grid_next( Grid *grid, RuleSet *rules );

/** @brief Update grid to previous values.
 *
 * @param x   Amount of columns in the array.
 * @param y   Amount of rows in the array.
 * @param arr Array to update.
 */
void Grid_prev( Grid *grid, RuleSet *rules );

/** @brief
 *
 */
int Grid_coiCount( Grid *grid );

/** @brief Update grid to previous values.
 *
 */
void Grid_coiAdd( Grid *grid, Cell *cell );

/** @brief Update grid to previous values.
 *
 */
void Grid_coiRem( Grid *grid, Cell *cell );


void Grid_switch_cell( Grid *grid, int x, int y );

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
