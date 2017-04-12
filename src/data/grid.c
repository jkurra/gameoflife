#include "grid.h"
#include <time.h>

typedef struct
{
    /** @brief
     *
     */
    CellArray *tmpAlive;
    Grid *grid;

    RuleSet *rules;
    /** @brief
     *
     */
    //int coiCount;

} GridAndTmp;

Cell **addCell1( Cell **array, Cell *toAdd, size_t oldSize );


void *nbrUpdateThread(void *arg)
{
    GridAndTmp *tmp = (GridAndTmp*)arg;

    for(unsigned int i=tmp->tmpAlive->count; i--; ) {
        //tmp->grid->lArray->c_array[i] = //Cell_new(tmp->tmpAlive->c_array[i]->row, tmp->tmpAlive->c_array[i]->col);

        tmp->grid->lArray->c_array[i]->state = 1;

        //CellArray_set( tmp->grid->lArray, STATE, i, 1 );
        if(tmp->grid->gArray->g_grid[tmp->grid->lArray->c_array[i]->row][tmp->grid->lArray->c_array[i]->col]) {
            tmp->grid->gArray->g_grid[tmp->grid->lArray->c_array[i]->row][tmp->grid->lArray->c_array[i]->col]->state   = 1;
            tmp->grid->gArray->g_grid[tmp->grid->lArray->c_array[i]->row][tmp->grid->lArray->c_array[i]->col]->checked = 0;
        }
        Cell_free(tmp->tmpAlive->c_array[i]);
    }

    tmp->grid->lArray->count = tmp->tmpAlive->count;
    free(tmp->tmpAlive->c_array);
    tmp->tmpAlive->c_array = NULL;
    free(tmp->tmpAlive);
    tmp->tmpAlive = NULL;

    return NULL;
}

void *gridClearThread(void *arg)
{
    Grid *grid = (Grid*)arg;

    GridArray_empty(grid->gArray);
    /*for(unsigned int i=grid->gArray->rows; i--; ) {
        for(int k=grid->gArray->cols; k--; ) {
           if(grid->gArray->g_grid[i][k]) {
                grid->gArray->g_grid[i][k]->state = 0;
                grid->gArray->g_grid[i][k]->checked = 0;
            }
        }
    }*/
    return NULL;
}

void *gridCheckArrayThread(void *arg)
{
    GridAndTmp *tmp = (GridAndTmp*)arg;
    for(unsigned int i=tmp->grid->lArray->count; i--; ) {
    //for(unsigned int i=0;i<grid->coiCount; i+=2 ) {
        tmp->grid->lArray->c_array[i]->nbrs_count = Grid_nbrs( tmp->grid, tmp->grid->lArray->c_array[i] );
        if(Cell_next( tmp->grid->lArray->c_array[i], tmp->rules )) { // Next state is alive.
            tmp->grid->gArray->g_grid[tmp->grid->lArray->c_array[i]->row][tmp->grid->lArray->c_array[i]->col]->checked = 1;
            //addCell1( Cell **array, Cell *toAdd, size_t oldSize )
            //CellArray_add( tmp->tmpAlive, Cell_new(tmp->grid->lArray->c_array[i]->row, tmp->grid->lArray->c_array[i]->col));
            tmp->tmpAlive->c_array = addCell1( tmp->tmpAlive->c_array , Cell_new(tmp->grid->lArray->c_array[i]->row, tmp->grid->lArray->c_array[i]->col), tmp->tmpAlive->count );
            tmp->tmpAlive->count++;
        }
        CellArray_set( tmp->grid->lArray, CHECK, i, 1 );
    //    tmp->grid->lArray->c_array[i]->checked = 1;
        Grid_Nbrs_check( tmp->tmpAlive, tmp->grid, tmp->grid->lArray->c_array[i], tmp->rules );
    }
    printf("coicount: %d\n", tmp->tmpAlive->count);
    return NULL;
}


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

void GridArray_resize( Grid *grid, int new_rows, int new_cols )
{
//    printf("alloc new grid:[%d][%d]\n", new_rows, new_cols);
    grid->gArray->g_grid = (Cell***)realloc(grid->gArray->g_grid, (new_rows+1)*sizeof(Cell**));

    for(int i=0; i<new_rows; i++) {
        printf("alloc row: %d\n", i);
        grid->gArray->g_grid[i] = (Cell**)realloc(grid->gArray->g_grid[i], (new_cols+1)*sizeof(Cell*));//(Cell**)calloc((new_cols+1), sizeof(Cell*));///malloc((grid->cols+1)*sizeof(Cell*)); //(Cell**)realloc(grid->g_grid, (grid->cols+1)*sizeof(Cell*));
    }

    for(int i=0; i<new_rows; i++) {
        for(int k=0; k<new_cols; k++) {
            grid->gArray->g_grid[i][k] = Cell_new(i, k);//grid->g_grid[i][k];
            grid->gArray->g_grid[i][k]->checked = 0;
        }
    }
    for(int i=0; i<grid->lArray->count; i++) {
        if(grid->lArray->c_array[i]->row < new_rows && grid->lArray->c_array[i]->col < new_cols) {
            grid->gArray->g_grid[grid->lArray->c_array[i]->row][grid->lArray->c_array[i]->col] = Cell_new(grid->lArray->c_array[i]->row, grid->lArray->c_array[i]->col);
            grid->gArray->g_grid[grid->lArray->c_array[i]->row][grid->lArray->c_array[i]->col]->state = grid->lArray->c_array[i]->state;
            grid->gArray->g_grid[grid->lArray->c_array[i]->row][grid->lArray->c_array[i]->col]->checked = 0;
        }
    }
    /// TODO: Add removal of cells outside grid borders here. Otherwise program will crash later.
    for(int i=0; i<grid->lArray->count; i++) {
        if(grid->lArray->c_array[i]->row < new_rows && grid->lArray->c_array[i]->col < new_cols) {

        } else {
            CellArray_rem(grid->lArray, grid->lArray->c_array[i]);
        //    Grid_coiRem(grid,  Cell_new(grid->lArray->c_array[i]->row, grid->lArray->c_array[i]->col));
            continue;
        }
    }

    grid->gArray->rows = new_rows;
    grid->gArray->cols = new_cols;

}

void Grid_mod( Grid *grid, int operation, Grid_ptr *data )
{
    switch (operation) {
        case EMPTY:
            GridArray_empty(grid->gArray);
            break;
        case RESIZE:
        //    GridArray_resize( Grid *grid, int new_rows, int new_cols )
            GridArray_resize(grid, data->row, data->col);
            break;
        case RANDOM:
            GridArray_rand(grid->gArray);
            for(int i=0; i<grid->gArray->rows; i++){
                for(int k=0; k<grid->gArray->cols; k++) { /* Flip coin for each cell, value is 1 or 0 */
                   if(grid->gArray->g_grid[i][k]->state == 1) {
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

void Grid_prev( Grid *grid, RuleSet *rules )
{

}

void Grid_next( Grid *grid, RuleSet *rules )
{
    printf("We have %d cells to check\n", grid->lArray->count );
    if(grid) {
        /* This array is used to store tmp values of living cells. */

        CellArray *tmpAlive = CellArray_new(0); //(CellGrid*)calloc(1, sizeof(CellGrid));
        GridArray *tmpArray = GridArray_copy( grid->gArray );
        //Cell ***g_grid = Grid_copy_array( grid->g_grid, grid->rows, grid->cols );

        time_t start,end;
        start=clock();

        GridAndTmp *tmp1 = (GridAndTmp*)calloc(1, sizeof(GridAndTmp));
        tmp1->grid = grid;
        tmp1->tmpAlive = tmpAlive;
        tmp1->rules = rules;

        pthread_t *thread2 ;
        pthread_create(&thread2, NULL, gridCheckArrayThread, tmp1);
        pthread_join(thread2, NULL);

        pthread_t *thread1;
        pthread_create(&thread1, NULL, gridClearThread, grid);
        pthread_join(thread1, NULL);

        CellArray_empty(grid->lArray);
        CellArray_realloc(grid->lArray, tmpAlive->count);
    //    Grid_coiEmpty(grid);
    //    Grid_coiRealloc( grid, tmpAlive->count );

        GridAndTmp *tmp = (GridAndTmp*)calloc(1, sizeof(GridAndTmp));
        tmp->grid = grid;
        tmp->tmpAlive = tmpAlive;

        pthread_t *thread;
        //object->g_model->is_playing = 1;
        pthread_create(&thread, NULL, nbrUpdateThread, tmp);
        pthread_join(thread, NULL);
        end = clock();
        time_t t = (end-start);
        printf("array update time: %d:: %d\n", t, grid->lArray->count);
    //    grid = Grid_copy_array( grid, grid->rows, grid->cols );
    }

}

Cell **addCell1( Cell **array, Cell *toAdd, size_t oldSize )
{
    Cell **rtn = (Cell**)realloc(array, (oldSize+1)*sizeof(Cell*));//(Cell**)calloc(oldSize+1, sizeof(Cell*));//(Cell**)realloc(array, (oldSize+1)*sizeof(Cell*));
    rtn[oldSize] = toAdd;

    return rtn;
}

void Grid_Nbrs_check( CellArray *tmpAlive, Grid *grid, Cell *c, RuleSet *rules )
{
    unsigned int grid_x=c->row-1, grid_y=c->col-1;
    unsigned int finalX =c->row-1, finalY =c->col-1;

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
            if(grid->gArray->g_grid[grid_x][grid_y]->checked == 0 && grid->gArray->g_grid[grid_x][grid_y]->state == 0 ) {
                grid->gArray->g_grid[grid_x][grid_y]->nbrs_count = Grid_nbrs(grid, grid->gArray->g_grid[grid_x][grid_y]);
                grid->gArray->g_grid[grid_x][grid_y]->checked = 1;
                if(Cell_next( grid->gArray->g_grid[grid_x][grid_y], rules ) == 1) {
                    //CellArray_add(tmpAlive->c_array , Cell_new(grid_x,  grid_y));
                    tmpAlive->c_array = addCell1(tmpAlive->c_array , Cell_new(grid_x,  grid_y), tmpAlive->count);
                    tmpAlive->count++;
                }
            }
        }
    }
}

void Grid_switch( Grid *grid, int row, int col )
{
    if(grid) {
        switch (grid->gArray->g_grid[row][col]->state) {
            case 1: {
                //Cell *c = Cell_new( row, col );
                //Grid_coiRem( grid, Cell_new( row, col ) );
                CellArray_rem(grid->lArray, Cell_new(row, col));
                grid->gArray->g_grid[row][col]->state = 0;
                break;
            }
            case 0: {
                //Cell *c1 = Cell_new(row,col);
                CellArray_add(grid->lArray, Cell_new( row, col ) );
            //    Grid_coiAdd( grid, Cell_new( row, col ) );
                grid->gArray->g_grid[row][col]->state = 1;
                break;
            }
            default:
                break;
        }
    }
}

int Grid_nbrs( Grid *grid, Cell *cell) //int row, int col, int rows, int cols, int **grid )
{
    unsigned int c=0;
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
            if( grid->gArray->g_grid[grid_x][grid_y] && grid->gArray->g_grid[grid_x][grid_y]->state == 1 ) {
                if(grid_x != cell->row || grid_y != cell->col) {
                    c++;
                }
            }
        }
    }

    return c;
}

void grid_print( Grid *grid )
{
  printf("Printing array[%d][%d]:\n", grid->gArray->rows, grid->gArray->cols);
 /* if(grid->g_grid) {
    for(int i=0; i<grid->rows; i++) {
        printf("r:%d ", i);
        for(int k=0; k<grid->cols; k++) {
            if(grid->g_grid[i][k]){
                printf("[%d]", grid->g_grid[i][k]->state);
            }else {printf("[0]");}
        }
        printf(" \n");
    }*
}*/
}
