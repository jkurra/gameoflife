#ifndef GRIDARRAY_H_INCLUDED
#define GRIDARRAY_H_INCLUDED

#include <stdio.h>
#include <time.h>

#include "basearray.h"
#include "../cell.h"


typedef struct
{
    int rows, cols;
    Cell ***g_grid;

} GridArray;

GridArray *GridArray_new( int rows, int cols );

void GridArray_free( GridArray *array );

void GridArray_empty( GridArray *array );

GridArray *GridArray_copy( GridArray *grid );

#endif /* GRID_H_ */
