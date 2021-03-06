#include "grid.h"
#include <time.h>

typedef struct
{
    /** @brief
     *
     */
    Grid *tmp_grid;
    Grid *grid;

    RuleSet *rules;
    int index;
} GridAndTmp;

/** @brief Count current neighbours for a cell.
 *
 * Each cell in the grid has 0-8 neighbours. This function calculates those
 * neighbours using current x and y location of the cell. This is usefull since
 * it is often necessary to know how many neighbours certain cell has, for
 * example to predict their future state. This function doesn't have safety
 * checks for x and y, so make sure they are within maximum limits.
 *
 * @return  Count of neighbours for the given cell.
 */
int Grid_nbrs( Grid *grid, Cell *cell);

/** @brief Update grid to next values.
 *
 * Given two dimensional grid is updated to next state, using current states
 * of each "cell" and given rules to apply. Previous values in the grid are
 * deleted and therefore lost, so don't use this to "peek" next values, with an
 * array that you don't want to update. Rules are given as integer arrays. Each
 * item in array represents number of neighbours that gives or retains life for
 * the cell.
 *
 * @param x   Amount of columns in the array.
 * @param y   Amount of rows in the array.
 * @param arr array to be initalized.
 * @param live_a rules to apply when cell is currently alive.
 * @param live_d rules to apply when cell is currently dead.
 */
void Grid_next( Grid *grid, RuleSet *rules );

/** @brief Update grid to previous values.
 *
 * @param x   Amount of columns in the array.
 * @param y   Amount of rows in the array.
 * @param arr Array to update.
 */
void Grid_prev( Grid *grid, RuleSet *rules );


Grid *Grid_new( int rows, int cols )
{
    Grid *rtn = (Grid*)calloc(1, sizeof(Grid));

    rtn->gArray = GridArray_new(rows, cols);
    rtn->lArray = CellArray_new(0);

    rtn->updated = 1;

    return rtn;
}

void Grid_free( Grid *grid )
{
    GridArray_free(grid->gArray);
    CellArray_free(grid->lArray);

    free(grid);
    grid = NULL;

}

Grid *Grid_copy( Grid *grid )
{
    Grid *rtn = (Grid*)calloc(1, sizeof(Grid));

    rtn->gArray = GridArray_copy(grid->gArray);
    rtn->lArray = CellArray_copy(grid->lArray);

    rtn->updated = 1;

    return rtn;
}

void Grid_mod( Grid *grid, int operation, Grid_ptr *data )
{
    switch (operation) {
        case EMPTY:
            GridArray_empty(grid->gArray);
            break;
        case RESIZE:
        //    GridArray_resize( Grid *grid, int new_rows, int new_cols )
        	printf("new Grid size: x:%d, y:%d \n", grid->gArray->rows, grid->gArray->cols);
            GridArray_resize(grid->gArray, data->row, data->col);
            break;
        case RANDOM:
            GridArray_rand(grid->gArray);
            for(int i=0; i<grid->gArray->rows; i++){
                for(int k=0; k<grid->gArray->cols; k++) { /* Flip coin for each cell, value is 1 or 0 */
                //    printf("cell sstate %d\n", grid->gArray->g_array[i][k]->state);
                   if(grid->gArray->g_array[i][k]->state == 1) {
                        Cell *c = Cell_new(i, k);
                        c->state = 1;
                        CellArray_add(grid->lArray, c);
                        //Grid_coiAdd(grid, c);
                    }
                }
            }
            break;
        case SWITCH:
            Grid_switch(grid, data->row, data->col);
            break;
        case NEXT:
            Grid_next(grid, data->rules);
            break;
        case PREV:
            Grid_prev(grid, data->rules);
            break;
        default:
            break;
    }
}

int Grid_count( Grid *grid, int type )
{
    int rtn = -1;

    switch (type) {
        case 0:
            rtn = grid->gArray->rows*grid->gArray->cols;
            break;
        case 1:
            rtn = grid->lArray->base.count;
            break;
        default:
            break;
    }

    return rtn;
}

void Grid_set_nbrs( Grid *grid, int index, int new_nbrs )
{
    grid->lArray->c_array[index]->nbrs_count = new_nbrs;
}

void Grid_set_checked( Grid *grid, int row, int col, int new_checked )
{
    Cell *tmp = GridArray_get(grid->gArray, row, col);
    if(tmp) {
        tmp->checked = new_checked;
    }
    //grid->gArray->g_array[row][col]->checked = new_checked;
    //grid->lArray->c_array[index]->nbrs_count = new_nbrs;
}

void Grid_prev( Grid *grid, RuleSet *rules )
{

}

void *clearArrays(void *arg)
{
    GridAndTmp *tmp = (GridAndTmp*)arg;
    Grid *tmp_grid = tmp->tmp_grid;
    Grid*grid = tmp->grid;

    GridArray_empty(grid->gArray);
//    printf("Goint to reset array...\n" );
    GridArray_set_with_cellarray( grid->gArray, tmp_grid->lArray );
    CellArray_clear(grid->lArray);

    grid->lArray = CellArray_copy(tmp_grid->lArray);

}

void *arrays(void *arg)
{
    GridAndTmp *tmp = (GridAndTmp*)arg;
    Grid *tmp_grid = tmp->tmp_grid;
    Grid*grid = tmp->grid;
    RuleSet *rules = tmp->rules;
    int i = tmp->index;
    //printf("Index: %d::%d\n", i, grid->lArray->base.count);
        //Grid_set_nbrs( grid, i, Grid_nbrs(grid, CellArray_get(grid->lArray, i)));// tmp_grid->lArray->c_array[i] ) );
    Cell *c = CellArray_get(grid->lArray, i);
    int nbrs = Grid_nbrs(grid, c);
    c->nbrs_count = nbrs;
    //printf("Index: %d::%d\n", i, grid->lArray->base.count);
    if(Cell_next(c, rules) == 1) { //tmp1->grid->lArray->c_array[i], tmp1->rules )) {
            //printf("Moving to next round!\n");
        Grid_set_checked( tmp_grid, grid->lArray->c_array[i]->row, grid->lArray->c_array[i]->col, 1 );
        Cell *c = Cell_new(grid->lArray->c_array[i]->row, grid->lArray->c_array[i]->col);
        c->state = 1;
        CellArray_add(tmp_grid->lArray,c);
    }
    CellArray_set( grid->lArray, CHECK, i, 1 );
    Grid_Nbrs_check( tmp_grid->lArray, grid, grid->lArray->c_array[i], rules );
}

void *checkArrays(void *arg)
{
    GridAndTmp *tmp = (GridAndTmp*)arg;
    Grid *tmp_grid = tmp->tmp_grid;
    Grid*grid = tmp->grid;
    RuleSet *rules = tmp->rules;

    int count = Grid_count(grid, 1);
    pthread_t thread1[count];

    for(unsigned int i=Grid_count(grid, 1); i--; ) {
        Cell *c = CellArray_get(grid->lArray, i);
        int nbrs = Grid_nbrs(grid, c);
        if(c){
            c->nbrs_count = nbrs;
            //printf("Index: %d::%d\n", i, grid->lArray->base.count);
            if(Cell_next(c, rules) == 1) { //tmp1->grid->lArray->c_array[i], tmp1->rules )) {
                    //printf("Moving to next round!\n");
                Grid_set_checked( tmp_grid, grid->lArray->c_array[i]->row, grid->lArray->c_array[i]->col, 1 );
                Cell *c = Cell_new(grid->lArray->c_array[i]->row, grid->lArray->c_array[i]->col);
                c->state = 1;
                CellArray_add(tmp_grid->lArray,c);
            }
            CellArray_set( grid->lArray, CHECK, i, 1 );
            Grid_Nbrs_check( tmp_grid->lArray, grid, grid->lArray->c_array[i], rules );
        }
    }

}

void *emptyGridThread(void *arg)
{
    GridAndTmp *tmp = (GridAndTmp*)arg;

    Grid *tmp_grid = tmp->tmp_grid;
    Grid*grid = tmp->grid;
    RuleSet *rules = tmp->rules;
    GridArray_empty(grid->gArray);
}

void *copyGridThread(void *arg)
{
    GridAndTmp *tmp = (GridAndTmp*)arg;

    Grid *tmp_grid = tmp->tmp_grid;
    Grid*grid = tmp->grid;
    RuleSet *rules = tmp->rules;
    GridArray_set_with_cellarray( grid->gArray, tmp_grid->lArray );
}

void *checkGridThread(void *arg)
{
    GridAndTmp *tmp = (GridAndTmp*)arg;

    Grid *tmp_grid = tmp->tmp_grid;
    Grid*grid = tmp->grid;
    RuleSet *rules = tmp->rules;

    pthread_t thread1;
    pthread_create(&thread1, NULL, checkArrays, tmp);
    pthread_join(thread1, NULL);
/*
    pthread_t thread;
    pthread_create(&thread, NULL, clearArrays, tmp);ar
    pthread_join(thread, NULL);
*/
    pthread_t thread2;
    pthread_create(&thread2, NULL, emptyGridThread, tmp);
    pthread_join(thread2, NULL);

    //printf("starting grid copy...\n" );

    //grid_print( grid );

    pthread_t thread3;
    pthread_create(&thread3, NULL, copyGridThread, tmp);
    pthread_join(thread3, NULL);

    CellArray_clear(grid->lArray);

    grid->lArray = CellArray_copy(tmp_grid->lArray);
/*
    GridArray_empty(grid->gArray);
/*
    GridArray_set_with_cellarray( grid->gArray, tmp_grid->lArray );
    CellArray_clear(grid->lArray);

    grid->lArray = CellArray_copy(tmp_grid->lArray);*/

    return NULL;
}


void Grid_next( Grid *grid, RuleSet *rules )
{
    if(grid) {
        //printf("Cellarray size: %d\n", grid->lArray->count);
        /* This array is used to store tmp values of living cells. */
        Grid *tmp_grid = Grid_new(grid->gArray->rows, grid->gArray->cols);//Grid_copy(grid);
        GridAndTmp *arrays = (GridAndTmp*)calloc(1, sizeof(GridAndTmp));

        arrays->tmp_grid = tmp_grid;
        arrays->grid = grid;
        arrays->rules = rules;

        time_t start, end;
        start=clock();

        pthread_t thread;
        pthread_create(&thread, NULL, checkGridThread, arrays);

        if(thread) {
            pthread_join(thread, NULL);
        }
        /*
        Grid_free(grid);
        grid = tmp_grid;
        */
        free(arrays);
        arrays = NULL;

        //Grid_free(tmp_grid);

        end = clock();
        time_t t = (end-start);

        //rintf("array update time: %d:: %d\n", t, grid->lArray->count);
    }
}



void Grid_Nbrs_check( CellArray *tmpAlive, Grid *grid, Cell *c, RuleSet *rules )
{
    unsigned int grid_x = c->row-1, grid_y = c->col-1;
    unsigned int finalX = c->row-1, finalY = c->col-1;

    if(c->row-1 < 0) {
        finalX = c->row;
    }
    if(c->col-1 < 0) {
        finalY = c->col;
    } //printf("row 1 %d:%d\n",grid_x, grid_y);
    int max_COL =c->col+2, max_ROW = c->row+2;

    if(max_COL > grid->gArray->cols) {
        max_COL = c->col;
    }
    if(max_ROW > grid->gArray->rows) {
        max_ROW = c->row;
    }
    //for(grid_x=max_ROW-1; grid_x>=finalX; grid_x--) {
    //    for(grid_y=max_COL-1; grid_y>=finalY; grid_y--) {
    for(grid_x=finalX; grid_x<max_ROW; grid_x++) {
      for(grid_y=finalY; grid_y<max_COL; grid_y++) {
          Cell *c2 = Cell_new(grid_x, grid_y);
          Cell *tmp = GridArray_get(grid->gArray, grid_x, grid_y);
         /* if(!CellArray_has(grid->gArray->checked_cells, c2) && grid->gArray->grid_arr[grid_x][grid_y] == 0) {
         }*/
          if(tmp && tmp->checked == 0 && tmp->state == 0) {
              //GridArray_set(grid->gArray, grid_x, grid_y, 1);
              GridArray_get(grid->gArray, grid_x, grid_y)->checked = 1;
              GridArray_get(grid->gArray, grid_x, grid_y)->nbrs_count = Grid_nbrs(grid, grid->gArray->g_array[grid_x][grid_y]);
              if(Cell_next( grid->gArray->g_array[grid_x][grid_y], rules ) == 1) {
                  Cell *c = Cell_new(grid_x,  grid_y);
                  c->state = 1;
                 // c->checked = 1;
                  CellArray_add(tmpAlive, c );
              }
          }
          Cell_free(c2);
        }
    }
}

void Grid_switch( Grid *grid, int row, int col )
{
    if(grid) {
        switch (grid->gArray->g_array[row][col]->state) {
            case 1: {
                //Cell *c = Cell_new( row, col );
                //Grid_coiRem( grid, Cell_new( row, col ) );
                Cell *c = Cell_new(row,col);
                c->state = 0;
                CellArray_rem(grid->lArray, c);
                grid->gArray->g_array[row][col]->state = 0;
                break;
            }
            case 0: {
                Cell *c1 = Cell_new(row,col);
                c1->state = 1;
                CellArray_add(grid->lArray, c1 );
            //    Grid_coiAdd( grid, Cell_new( row, col ) );
                grid->gArray->g_array[row][col]->state = 1;
                break;
            }
            default:
                break;
        }
    }
}

int Grid_nbrs( Grid *grid, Cell *cell) //int row, int col, int rows, int cols, int **grid )
{
    unsigned int c=-1;
    if(grid && cell) {
        c = 0;
    //    int grid_x=cell->row-1, grid_y=cell->col-1;
        unsigned int grid_x=cell->row-1, grid_y=cell->col-1;
        unsigned int finalX=cell->row-1, finalY=cell->col-1;

        if(cell->row-1 < 0) {
            finalX = cell->row;
        }
        if(cell->col-1 < 0) {
            finalY = cell->col;
        } //printf("row 1 %d:%d\n",grid_x, grid_y);
        int max_COL =cell->col+2, max_ROW = cell->row+2;

        if(max_COL > grid->gArray->cols) {
            max_COL = cell->col;
        }
        if(max_ROW > grid->gArray->rows) {
            max_ROW = cell->row;
        }
        //for(grid_x=max_ROW-1; grid_x>=finalX; grid_x--) {
        //    for(grid_y=max_COL-1; grid_y>=finalY; grid_y--) {
        for(grid_x=finalX;grid_x<max_ROW ; grid_x++) {
            for(grid_y=finalY; grid_y<max_COL; grid_y++) {
                Cell *tmp = GridArray_get(grid->gArray, grid_x, grid_y);
                if( tmp && tmp->state == 1 ) {
                    if(grid_x != cell->row || grid_y != cell->col) {
                        c++;
                    }
                }
            }
        }
    }
    return c;
}

void grid_print( Grid *grid )
{
  printf("Printing array[%d][%d]:\n", grid->gArray->rows, grid->gArray->cols);
  if(grid->gArray) {
    for(int i=0; i<grid->gArray->rows; i++) {
        printf("r:%d ", i);
        for(int k=0; k<grid->gArray->cols; k++) {
            if(grid->gArray->g_array[i][k]){
                printf("[%d]", grid->gArray->g_array[i][k]->state);
            }else {printf("[0]");}
        }
        printf(" \n");
    }
    }
}
