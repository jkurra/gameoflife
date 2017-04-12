#include "gridarray.h"

GridArray *GridArray_new( int rows, int cols )
{
    GridArray *arr = (GridArray *)calloc(rows+1, sizeof(GridArray));
    arr->rows = rows;
    arr->cols = cols;
    arr->g_grid = (Cell***)calloc(rows+1, sizeof(Cell**));
    for(int i=0; i<rows; i++) {
        arr->g_grid[i] = (Cell**)calloc(cols+1, sizeof(Cell*));
    }
    for(int i=0; i<rows; i++) {
        for(int k=0; k<cols; k++) {
            arr->g_grid[i][k] = Cell_new(i, k);
            arr->g_grid[i][k]->state   = 0;
            arr->g_grid[i][k]->checked = 0;
        }
    }
    return arr;
}

void GridArray_free( GridArray *array )
{

}

GridArray *GridArray_copy( GridArray *grid )
{
    GridArray *arr = GridArray_new( grid->rows, grid->cols );// (GridArray *)calloc(grid->rows+1, sizeof(GridArray));

    for(int i=0; i<grid->rows; i++) {
        for(int k=0; k<grid->cols; k++) {
            arr->g_grid[i][k] = Cell_new(i, k);
            arr->g_grid[i][k]->state    = grid->g_grid[i][k]->state;
            arr->g_grid[i][k]->checked  = grid->g_grid[i][k]->checked;
        }
    }

    return arr;
}


void GridArray_rand( GridArray *array )
{
    if(array->g_grid) {
        int k_count = 0;
        for(int i=0; i<array->rows; i++){
            for(int k=0; k<array->cols; k++) { /* Flip coin for each cell, value is 1 or 0 */
                int rval = rand()%2;
                array->g_grid[i][k]->state = rval;
            }
        }
    }
}

void GridArray_empty( GridArray *array )
{
    for(int i=0; i<array->rows; i++) {
        for(int k=0; k<array->cols; k++) {
            if(array->g_grid[i][k]) {
                array->g_grid[i][k]->state = 0;
                array->g_grid[i][k]->checked = 0;
            }
        }
    }
}
