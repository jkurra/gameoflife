#ifndef CELLARRAY_H_INCLUDED
#define CELLARRAY_H_INCLUDED

#include <stdio.h>
#include <time.h>

#include "basearray.h"
#include "../cell.h"

#define STATE 0
#define CHECK 1

/** @brief CellArray structure.
 *
 *  Structure describing a CellArray, which consists of storage with cells
 *  in it and counter that keeps track of the size of the array. Other values
 *  may be added as needed. All values of CellArray may only be accessed using
 *  member functions to keep things coherent. CellArray creation and deletion
 *  are done using specialized _new() and _free() functions that handle all
 *  memory management and pointers.
 */
typedef struct
{
    /** @brief Properties of BaseArray.
     *
     *  Provides access to BaseArray properties for CellArray structure, which
     *  means this class needs less private values.
     */
    BaseArray base;

    /** @brief Pointer to array of cells.
     *
     *  Provides access to array, which may be used to store cell pointers.
     *  Array is created, deleted, accessed and dynamically resized
     *  using member functions and only member functions. This is done in
     *  order to ensure safe and efficient memory management.
     */
    Cell **c_array;

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

/** @brief Copy values from given grid to array.
 *
 */
void CellArray_copy_values( CellArray *dest, CellArray *toCopy );

/** @brief Add new cell to the end of cell-array.
 *
 */
void CellArray_add( CellArray *array, Cell *cell );

/** @brief Set value of a cell property in given index.
 *
 */
void CellArray_set( CellArray *array, int val, int index, int new_state );

/** @brief Set value of a cell property in given index.
 *
 */
int CellArray_has( CellArray *array, Cell *cell);

/** @brief
 *
 */
Cell *CellArray_get( CellArray *array, int index );

#endif /* GRID_H_ */
