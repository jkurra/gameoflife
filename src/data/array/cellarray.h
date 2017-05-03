#ifndef CELLARRAY_H_INCLUDED
#define CELLARRAY_H_INCLUDED

#include <stdio.h>
#include <time.h>

#include "basearray.h"
#include "../cell.h"

#define STATE 0
#define CHECK 1

/**
 *
 */
typedef struct
{
    BaseArray base;
    
    /**
     *
     */
    Cell **c_array;

    /**
     *
     */
    int count;

} CellArray;

/** @brief Initialize new array with given size.
 *
 */
CellArray *CellArray_new();

/** @brief Free given CellArray.
 *
 */
void CellArray_free( CellArray *array );

/** @brief Set values to 0 in every cell in array.
 *
 *  Set array size to 0 and free pointers.
 */
void CellArray_clear( CellArray *array );

/** @brief Set values to 0 in every cell in array.
 *
 */
void CellArray_empty( CellArray *array );

/** @brief Returns copy of given CellArray.
 *
 */
CellArray *CellArray_copy( CellArray *toCopy );

/** @brief Add new cell to the end of cell-array.
 *
 */
void CellArray_add( CellArray *array, Cell *cell );

/** @brief Set value of a cell property in given index.
 *
 */
void CellArray_set( CellArray *array, int val, int index, int new_state );

int CellArray_has( CellArray *array, Cell *cell);

/** @brief
 *
 */
Cell *CellArray_get( CellArray *array, int index );

#endif /* GRID_H_ */