#include "gridarray.h"

GridArray *GridArray_new( int rows, int cols )
{
    /*
     *
     */
    GridArray *arr = (GridArray *)calloc(rows, sizeof(GridArray));

    /*
     *
     */
    arr->rows = rows;
    arr->cols = cols;
    /*
     *  Allocate space for rows and columns in grid.
     */
    arr->g_array = (Cell***)calloc(rows, sizeof(Cell**));
    for(int i=0; i<rows; i++) {
        arr->g_array[i] = (Cell**)calloc(cols, sizeof(Cell*));
    }
    // TODO: this array replaces ol one
    /*arr->grid_arr = (int**)calloc(rows, sizeof(int*));
    for(int i=0; i<rows; i++) {
        arr->grid_arr[i] = (int*)calloc(cols, sizeof(int));
    }*/

    for(int i=0; i<rows; i++) {
        for(int k=0; k<cols; k++) {
            arr->g_array[i][k] = 0;
        }
    }
    /*
     *  create new cells for allocated spaces in grid and assing cells with default
     *  values which are always 0.
     */
    for(int i=0; i<rows; i++) {
        for(int k=0; k<cols; k++) {
            arr->g_array[i][k] = Cell_new(i, k);
            arr->g_array[i][k]->state   = 0;
            arr->g_array[i][k]->checked = 0;
        }
    }
    return arr;
}

void GridArray_free( GridArray *array )
{
    /*
     *  Free cell in each slot of the grid.
     */
    for(int i=0; i<array->rows; i++) {
        for(int k=0; k<array->cols; k++) {
            if(array->g_array[i][k]) {
            //    printf("freeing cell at %d:%d. \n", i,k);
                Cell_free(array->g_array[i][k]);
            }
        }
    }

    for(int i=0; i<array->rows; i++) {
        free(array->g_array[i]);
        array->g_array[i] = NULL;
    }

    free(array->g_array);
    array->g_array = NULL;

    free(array);
    array = NULL;
}

void GridArray_empty( GridArray *array )
{
    for(int i=0; i<array->rows; i++) {
        for(int k=0; k<array->cols; k++) {
            Cell *tmp = GridArray_get(array, i, k);
            if(tmp) {
                tmp->state   = 0;
                tmp->checked = 0;
            }
            /*if(array->g_array[i][k]) {
                array->g_array[i][k]->state = 0;
                array->g_array[i][k]->checked = 0;
            }*/
        }
    }
}

// TODO: remove 1 and replace function in grid.c
void GridArray_resize( GridArray *grid, int new_rows, int new_cols )
{
    GridArray *tmpcopy = GridArray_copy(grid);
    int old_rows = grid->rows;
    int old_cols = grid->cols;

    grid->rows = new_rows;
    grid->cols = new_cols;
    /*
     * First free all cells outside new borders, if new grid is smaller than previous.
     */
    if(new_rows < old_rows ) {
        for(int i=new_rows; i<old_rows ; i++) {
            //GridArray_get();
            //Cell_free(grid->g_array[i]);
        }
    }
    if(new_rows < old_cols) {
        for(int i=new_cols; i<old_cols; i++) {

            //Cell_free(grid->g_array[i]);
        }
    }
    /*
     * Reallocate grid with new values.
     */

    grid->g_array = (Cell***)realloc(grid->g_array, (new_rows+1)*sizeof(Cell**));

    for(int i=0; i<new_rows; i++) {
        grid->g_array[i] = (Cell**)calloc(new_cols, sizeof(Cell*));
    }

    for(int i=0; i<new_rows; i++) {
        for(int k=0; k<new_cols; k++) {
            grid->g_array[i][k] = Cell_new(i, k);
            grid->g_array[i][k]->state = 0;
            grid->g_array[i][k]->checked = 0;
        }
    }
    /*
     *  Reset values from tmp array.
     */
    for(int i=0; i<old_rows; i++) {
        for(int k=0; k<old_cols; k++) {
            Cell *c = GridArray_get(tmpcopy, i, k);
            if(c) {
                if(i<new_rows && k<new_cols) {
                    grid->g_array[i][k]->state   = c->state;
                    grid->g_array[i][k]->checked = c->checked;
                }
            }
        }
    }
    GridArray_free(tmpcopy);
}

GridArray *GridArray_copy( GridArray *grid )
{
    GridArray *arr = GridArray_new(grid->rows, grid->cols);// (GridArray *)calloc(grid->rows+1, sizeof(GridArray));

    for(int i=0; i<grid->rows; i++) {
        for(int k=0; k<grid->cols; k++) {
            arr->g_array[i][k] = Cell_new(i, k);
            arr->g_array[i][k]->state   = grid->g_array[i][k]->state;
            arr->g_array[i][k]->checked = grid->g_array[i][k]->checked;
        }
    }

    return arr;
}

void GridArray_copy_values( GridArray *dest, GridArray *source )
{

    for(int i=0; i<source->rows; i++) {
    /*/    if( i <= dest->rows ) {
            break;
        }*/
        for(int k=0; k<source->cols; k++) {
            /*if( i <= dest->cols ) {
                break;
            }*/
            //arr->g_array[i][k] = Cell_new(i, k);
            dest->g_array[i][k]->state   = source->g_array[i][k]->state;
            dest->g_array[i][k]->checked = source->g_array[i][k]->checked;
        }
    }
}

void GridArray_set_with_cellarray( GridArray *dest, CellArray *source )
{
//    printf("cellarray set: %d \n", source->count );
    for(int i=0; i<source->count; i++) {
        Cell *c = CellArray_get(source, i);
    //    printf("cellarray set [%d][%d]::%d \n", c->row, c->col, c->state );
        Cell *grid_c = GridArray_get(dest, c->row,c->col);
        if(grid_c) {
            grid_c->state = c->state;
            grid_c->checked = c->checked;
        }
        //dest->g_array[c->row][c->col]->state   = c->state;
        //dest->g_array[c->row][c->col]->checked = c->checked;

    }

}

void GridArray_rand( GridArray *array )
{
    if(array->g_array) {
        int k_count = 0;
        for(int i=0; i<array->rows; i++){
            for(int k=0; k<array->cols; k++) { /* Flip coin for each cell, value is 1 or 0 */
                int rval = rand()%2;
                array->g_array[i][k]->state = rval;
            }
        }
    }
}

Cell *GridArray_get( GridArray *array, int row, int col )
{
    Cell *rtn = NULL;

//    printf("Get cell: x:%d-%d, y:%d-%d\n", array->rows, row, array->cols, col);
    if(array && row < array->rows && row >= 0 && col < array->cols && col >= 0) {
        if(array->g_array[row][col]) {
            rtn = array->g_array[row][col];
        }
    }

    return rtn;
}

void GridArray_set( GridArray *grid, int row, int col, int state )
{
    grid->g_array[row][col]->state = state;
}
