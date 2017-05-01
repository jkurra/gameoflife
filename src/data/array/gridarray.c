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
    arr->g_grid = (Cell***)calloc(rows, sizeof(Cell**));
    for(int i=0; i<rows; i++) {
        arr->g_grid[i] = (Cell**)calloc(cols, sizeof(Cell*));
    }
    // TODO: this array replaces ol one
    /*arr->grid_arr = (int**)calloc(rows, sizeof(int*));
    for(int i=0; i<rows; i++) {
        arr->grid_arr[i] = (int*)calloc(cols, sizeof(int));
    }*/

    for(int i=0; i<rows; i++) {
        for(int k=0; k<cols; k++) {
            arr->g_grid[i][k] = 0;
        }
    }
    /*
     *  create new cells for allocated spaces in grid and assing cells with default
     *  values which are always 0.
     */
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
    /*
     *  Free cell in each slot of the grid.
     */
    for(int i=0; i<array->rows; i++) {
        for(int k=0; k<array->cols; k++) {
            if(array->g_grid[i][k]) {
            //    printf("freeing cell at %d:%d. \n", i,k);
                Cell_free(array->g_grid[i][k]);
            }
        }
    }

    for(int i=0; i<array->rows; i++) {
        free(array->g_grid[i]);
        array->g_grid[i] = NULL;
        //arr->g_grid[i] = (Cell**)calloc(cols, sizeof(Cell*));
    }

    free(array->g_grid);
    array->g_grid = NULL;

    free(array);
    array = NULL;
}

// TODO: remove 1 and replace function in grid.c
void GridArray_resize1( GridArray *grid, int new_rows, int new_cols )
{
    /*
     * First free all cells outside new borders, if new grid is smaller than previous.
     */
    if(new_rows < grid->rows) {
        for(int i=new_rows; i<grid->rows; i++) {
            Cell_free(grid->g_grid[i]);
        }
    }
    if(new_rows < grid->cols) {
        for(int i=new_cols; i<grid->cols; i++) {
            Cell_free(grid->g_grid[i]);
        }
    }
    /*
     * Reallocate grid with new values.
     */

    grid->g_grid = (Cell***)realloc(grid->g_grid, (new_rows)*sizeof(Cell**));
    //if(new_cols != grid->cols) {
    if(grid->cols != new_cols) {
        for(int i=0; i<new_rows; i++) {
        /*    if(grid->g_grid[i] == NULL ) {
                grid->g_grid[i] = (Cell**)calloc(new_cols, sizeof(Cell*));
            } else {*/
            //arr->g_grid[i] = (Cell**)calloc(cols, sizeof(Cell*));
            //if(grid->cols != new_cols) {
                printf("new cell alloc i:%d=x:%d-%d y:%d:%d\n", i, grid->rows, new_rows, grid->cols, new_cols);
                grid->g_grid[i] = (Cell**)realloc(grid->g_grid[i], (new_cols)*sizeof(Cell*));
                for(int k=grid->cols; k<new_cols; k++) {
                    grid->g_grid[i][k] = Cell_new(i, k);//grid->g_grid[i][k];
                    grid->g_grid[i][k]->state = 0;
                    grid->g_grid[i][k]->checked = 0;
                }
            ///}
            //}
        }
    }
    else {
        for(int i=grid->rows; i<new_rows; i++) {
            grid->g_grid[i] = (Cell**)calloc(new_cols, sizeof(Cell*));
            for(int k=0; k<grid->cols; k++) {
                grid->g_grid[i][k] = Cell_new(i, k);//grid->g_grid[i][k];
                grid->g_grid[i][k]->state = 0;
                grid->g_grid[i][k]->checked = 0;
            }
        }
    }
    //}
    /*
     * If new grid is bigger than previous, fill newly allocated spaces with empty cells.
     */
    /*for(int i=grid->rows; i<new_rows; i++) {
        for(int k=grid->cols; k<new_cols; k++) {
            grid->g_grid[i][k] = Cell_new(i, k);//grid->g_grid[i][k];
            grid->g_grid[i][k]->state = 0;
            grid->g_grid[i][k]->checked = 0;
        }
    }*/

    grid->rows = new_rows;
    grid->cols = new_cols;
}

GridArray *GridArray_copy( GridArray *grid )
{
    GridArray *arr = GridArray_new(grid->rows, grid->cols);// (GridArray *)calloc(grid->rows+1, sizeof(GridArray));

    for(int i=0; i<grid->rows; i++) {
        for(int k=0; k<grid->cols; k++) {
            arr->g_grid[i][k] = Cell_new(i, k);
            arr->g_grid[i][k]->state   = grid->g_grid[i][k]->state;
            arr->g_grid[i][k]->checked = grid->g_grid[i][k]->checked;
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
            //arr->g_grid[i][k] = Cell_new(i, k);
            dest->g_grid[i][k]->state   = source->g_grid[i][k]->state;
            dest->g_grid[i][k]->checked = source->g_grid[i][k]->checked;
        }
    }
}

void GridArray_set_with_cellarray( GridArray *dest, CellArray *source )
{
//    printf("cellarray set: %d \n", source->count );
    for(int i=0; i<source->count; i++) {
        Cell *c = CellArray_get(source, i);
    //    printf("cellarray set [%d][%d]::%d \n", c->row, c->col, c->state );
        dest->g_grid[c->row][c->col]->state   = c->state;
        dest->g_grid[c->row][c->col]->checked = c->checked;

    }

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

Cell *GridArray_get( GridArray *array, int row, int col )
{
    Cell *rtn = NULL;

//    printf("Get cell: x:%d-%d, y:%d-%d\n", array->rows, row, array->cols, col);
    if(array && row < array->rows && row >= 0 && col < array->cols && col >= 0) {
        if(array->g_grid[row][col]) {
            rtn = array->g_grid[row][col];
        }
    }

    return rtn;
}

void GridArray_set( GridArray *grid, int row, int col, int state )
{
    grid->g_grid[row][col]->state = state;
}
