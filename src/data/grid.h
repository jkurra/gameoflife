#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <stdio.h>
#include <time.h>

#include "cell.h"

/* Grid modify functions. */
#define EMPTY  0
#define RESIZE 1
#define RANDOM 2
#define SWITCH 3
#define NEXT 4
#define PREV 5

/** @brief Structure for updating Grid.
 *
 *  Structure intended to be used for grid modifications.
 */
typedef struct
{
    int row, col;
    RuleSet *rules;

} Grid_ptr;

/** @brief Structure for GameGrid object.
 *
 */
typedef struct
{
    /** @brief
     *
     */
    Cell ***g_grid;

    /** @brief
     *
     */
    int rows;

    /** @brief
     *
     */
    int cols;

    /** @brief
     *
     */
    Cell **coiArray;

    /** @brief
     *
     */
    int coiCount;
    int updated;

} Grid;

/** @brief
 *
 */
typedef struct
{
    /** @brief
     *
     */
    Cell **coiArray;

    /** @brief
     *
     */
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

/** @brief Modify grid dimensions and data.
 *
 *
 */
void Grid_mod( Grid *grid, int operation, Grid_ptr *data );

#endif /* GRID_H_ */
