#ifndef GRIDARRAY_H_INCLUDED
#define GRIDARRAY_H_INCLUDED

#include <stdio.h>
#include <time.h>

#include "basearray.h"
#include "cellarray.h"
#include "../cell.h"

/** @brief Set value of a cell property in given index.
 *
 */
typedef struct
{
    /**
     *
     */
    Cell ***g_grid;

    /**
     *
     */
    int rows, cols;

} GridArray;

/** @brief Set value of a cell property in given index.
 *
 */
GridArray *GridArray_new( int rows, int cols );

/** @brief Set value of a cell property in given index.
 *
 */
void GridArray_free( GridArray *array );

/** @brief Set value of a cell property in given index.
 *
 */
void GridArray_empty( GridArray *array );

/** @brief Set value of a cell property in given index.
 *
 */
GridArray *GridArray_copy( GridArray *grid );

/** @brief Set value of a cell property in given index.
 *
 */
 Cell *GridArray_get( GridArray *grid, int row, int col );

 /** @brief Set value of a cell property in given index.
  *
  */
void GridArray_set( GridArray *grid, int row, int col, int state );

#endif /* GRID_H_ */
