#ifndef BASEARRAY_H_INCLUDED
#define BASEARRAY_H_INCLUDED

#include <stdio.h>
#include <time.h>

#define GRID_A 0
#define CELL_A 1

/**
 *
 */
typedef struct
{
    /**
     *
     */
    int row;

    /**
     *
     */
    int col;

} arr_dim;

/**
 *
 */
typedef struct
{
    /** @brief Type of "subclass" array.
     *
     */
    int type;

    /** @brief count of all cells in array.
     *
     */
    int count;

} BaseArray;

#endif /* GRID_H_ */
