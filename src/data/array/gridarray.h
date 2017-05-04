#ifndef GRIDARRAY_H_INCLUDED
#define GRIDARRAY_H_INCLUDED

#include <stdio.h>
#include <time.h>

#include "basearray.h"
#include "cellarray.h"
#include "../cell.h"

typedef struct
{
    /**
     *
     */
    BaseArray base;

    /** @brief Array representing two dimensional plane with cells.
     *
     *  For efficiency reasons this array only has integer values 1 or 0,
     *  that represent cell with a certain state. Position and value may be
     *  used to create Cell structures.
     *  TODO: replace g_array with this array to be more effeci.
     */
    Cell ***g_array;

    /** @brief Dimensions of g_array.
     *
     */
    int rows, cols;

} GridArray;

/** @brief Set value of a cell property in given index.
 *
 */
GridArray *GridArray_new( int rows, int cols );

/** @brief Free allocated memory for grid and cells.
 *
 */
void GridArray_free( GridArray *array );

/** @brief Reset every cell in grid to 0 values.
 *
 */
void GridArray_empty( GridArray *array );

/** @brief Return dynamically allocated pointer to copied array.
 *
 */
GridArray *GridArray_copy( GridArray *grid );

/** @brief Get value of a cell property in given index.
 *
 */
 Cell *GridArray_get( GridArray *grid, int row, int col );

 /** @brief Set value of a cell property in given index.
  *
  */
void GridArray_set( GridArray *grid, int row, int col, int state );

#endif /* GRID_H_ */
