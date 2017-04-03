#include "grid.h"
#include <time.h>

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

/** @brief Print two dimensional array to console.
 *
 */
void grid_print(Grid *grid );

Grid *Grid_new( int rows, int cols )
{
    /* */
    Grid *rtn = (Grid*)calloc(1, sizeof(Grid));
    /*
     *
     */
    rtn->rows = rows;
    rtn->cols = cols;
    /*
     *
     */
    rtn->g_grid = (Cell***)calloc(rtn->rows+1, sizeof(Cell**));
    for(int i=rows; i--;) {
        rtn->g_grid[i] = (Cell**)calloc(rtn->cols+1, sizeof(Cell*));
    }
    /*
     *
     */
    for(int i=rtn->rows; i--;) {
        for(int k=rtn->cols; k--;) {
            rtn->g_grid[i][k] = Cell_new(i, k);
            rtn->g_grid[i][k]->checked = 0;
        }
    }
    /*
     *
     */
    rtn->coiCount = 0;
    rtn->coiArray = NULL;
    rtn->updated=1;
    return rtn;
}

void Grid_free( Grid *grid )
{
    if(grid->g_grid) {
        for(int i=0; i<grid->rows; i++) {
            for(int k=0; k<grid->cols; k++) {
                Cell_free(grid->g_grid[i][k]);
            }
            free(grid->g_grid[i]);
            grid->g_grid[i] = NULL;
       }
    }

    for(int i=0; i<grid->coiCount; i++) {
        Cell_free(grid->coiArray[i]);
    }

    free(grid->coiArray);
    grid->coiArray = NULL;

    grid->rows = -1;
    grid->cols = -1;

    free(grid);
    grid = NULL;

}

void Grid_mod( Grid *grid, int operation, Grid_ptr *data )
{
    switch (operation) {
        case EMPTY:
            Grid_empty(grid);
            break;
        case RESIZE:
            Grid_resize(grid, data->row, data->col);
            break;
        case RANDOM:
            Grid_rand(grid);
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

Cell **addCell1( Cell **array, Cell *toAdd, size_t oldSize );
Cell **remCell( Cell **array, size_t size, int x, int y );

int Grid_coiCount( Grid *grid )
{
    return grid->coiCount;
}

void Grid_coiAdd( Grid *grid, Cell *cell )
{
    if(grid) {
        grid->coiArray = realloc(grid->coiArray, (grid->coiCount+1)*sizeof(Cell*));
        grid->coiArray[grid->coiCount] = cell;

        grid->coiCount++;
    }
}

void remElem1( Cell** array, int index, int len )
{
    int i=0;
    for(i=index; i<len-1; i++) {
        Cell_free(array[i]);
        array[i] = NULL;
        array[i] = array[i+1];
    }
}

void Grid_coiRealloc( Grid *grid, size_t newSize )
{
    for(int i=grid->coiCount; i--; ) {
        Cell_free(grid->coiArray[i]);
    }
    free(grid->coiArray);
    grid->coiArray = NULL;

    grid->coiArray = (Cell**)calloc(newSize, sizeof(Cell*));

}

void Grid_coiRem( Grid *grid, Cell *cell )
{
    if(grid) {
        for(int i=0; i<grid->coiCount; i++) {
            //printf("size: %d, %d\n", i, array[i]->x);
            if(grid->coiArray[i]->row == cell->row && grid->coiArray[i]->col == cell->col) {
                remElem1(grid->coiArray, i, grid->coiCount);
                grid->coiArray = realloc(grid->coiArray, (grid->coiCount-1)*sizeof(Cell*));
                grid->coiCount--;
                break;
            }
        }
    }
}

void Grid_coiEmpty( Grid *grid )
{

    if(grid) {
        if(grid->coiArray) {
            //for(int i=0; i<grid->coiCount; i++) {
            for(int i=grid->coiCount; i--;) {
                free(grid->coiArray[i]);
                grid->coiArray[i] = NULL;
            }

            grid->coiCount = 0;
        }
    }
}

void Grid_resize( Grid *grid, int new_rows, int new_cols )
{
//    printf("alloc new grid:[%d][%d]\n", new_rows, new_cols);
    grid->g_grid = (Cell***)realloc(grid->g_grid, (new_rows+1)*sizeof(Cell**));
    for(int i=0; i<new_rows; i++) {
        printf("alloc row: %d\n", i);
        grid->g_grid[i] = (Cell**)calloc((new_cols+1), sizeof(Cell*));///malloc((grid->cols+1)*sizeof(Cell*)); //(Cell**)realloc(grid->g_grid, (grid->cols+1)*sizeof(Cell*));
    }

    for(int i=0; i<new_rows; i++) {
        for(int k=0; k<new_cols; k++) {
            grid->g_grid[i][k] = Cell_new(i, k);//grid->g_grid[i][k];
            grid->g_grid[i][k]->checked = 0;
        }
    }
    for(int i=0; i<grid->coiCount; i++) {
        if(grid->coiArray[i]->row < new_rows && grid->coiArray[i]->col < new_cols) {
            grid->g_grid[grid->coiArray[i]->row][grid->coiArray[i]->col] = Cell_new(grid->coiArray[i]->row, grid->coiArray[i]->col);
            grid->g_grid[grid->coiArray[i]->row][grid->coiArray[i]->col]->state = grid->coiArray[i]->state;
            grid->g_grid[grid->coiArray[i]->row][grid->coiArray[i]->col]->checked = 0;
        }
    }
    /// TODO: Add removal of cells outside grid borders here. Otherwise program will crash later.
    for(int i=0; i<grid->coiCount; i++) {
        if(grid->coiArray[i]->row < new_rows && grid->coiArray[i]->col < new_cols) {

        } else {
            Grid_coiRem(grid,  Cell_new(grid->coiArray[i]->row, grid->coiArray[i]->col));
            continue;
        }
    }
    grid->rows = new_rows;
    grid->cols = new_cols;

}

void Grid_empty( Grid *grid )
{
    for(int i=0; i<grid->rows; i++) {
        for(int k=0; k<grid->cols; k++) {
            if(grid->g_grid[i][k]) {
                grid->g_grid[i][k]->state = 0;
            }
        }
    }
}


Cell **addCell1( Cell **array, Cell *toAdd, size_t oldSize )
{
    Cell **rtn = (Cell**)realloc(array, (oldSize+1)*sizeof(Cell*));//(Cell**)calloc(oldSize+1, sizeof(Cell*));//(Cell**)realloc(array, (oldSize+1)*sizeof(Cell*));
    rtn[oldSize] = toAdd;

    return rtn;
}

void remElem( Cell** array, int index, int len )
{
    int i=0;
    for(i=index; i<len-1; i++) {
        array[i] = array[i+1];
    }
}

Cell **remCell( Cell **array, size_t size, int row, int col )
{
    for(int i=0; i<size; i++) {
        //printf("size: %d, %d\n", i, array[i]->x);
        if(array[i]->row == row && array[i]->col == col) {
            remElem(array, i, size);
            array = realloc(array, (size-1)*sizeof(Cell*));
            break;
        }
    }

    return array;
}

void remAllCells( Cell **array, size_t size )
{
    for(int i=0; i<size; i++) {
        free(array[i]);
        array[i] = NULL;
    }

    free(array);
    array = NULL;
}

void Grid_rand( Grid *grid )
{
    if(grid->g_grid) {
        int k_count = 0;
        for(int i=0; i<grid->rows; i++){
            for(int k=0; k<grid->cols; k++) { /* Flip coin for each cell, value is 1 or 0 */
                int rval = rand()%2;
                grid->g_grid[i][k]->state = rval;
                /*if(rval == 1 && k_count < 500 ) {
                    k_count++;
                    grid->g_grid[i][k]->state = rval;
                }else {
                    grid->g_grid[i][k]->state = 0;
                }*/

            }
        }
        for(int i=0; i<grid->rows; i++){
            for(int k=0; k<grid->cols; k++) { /* Flip coin for each cell, value is 1 or 0 */
                if(grid->g_grid[i][k]->state == 1) {
                    Cell *c = Cell_new(i, k);
                    c->state = 1;
                    Grid_coiAdd(grid, c);
                }
            }
        }
    }
}

void Grid_addCell( Grid *grid, Cell *cell )
{
    grid->g_grid[cell->row][cell->col] = cell;
}

CellGrid *addToGrid( CellGrid *cg, Cell *toAdd, size_t oldSize )
{
    cg->coiArray = realloc(cg->coiArray, (cg->coiCount+1)*sizeof(Cell*));
        //printf("added new cell at: %d\n", oldSize);
    cg->coiArray[cg->coiCount] = toAdd;

    return cg;
}

void Grid_prev( Grid *grid, RuleSet *rules )
{

}

void Grid_Nbrs_check( CellGrid *tmpAlive, Grid *grid, Cell *c, RuleSet *rules )
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

    if(max_COL > grid->cols) {
        max_COL = c->col;
    }
    if(max_ROW > grid->rows) {
        max_ROW = c->row;
    }
    //for(grid_x=max_ROW-1; grid_x>=finalX; grid_x--) {
    //    for(grid_y=max_COL-1; grid_y>=finalY; grid_y--) {
    for(grid_x=finalX; grid_x<max_ROW; grid_x++) {
      for(grid_y=finalY; grid_y<max_COL; grid_y++) {
            if(grid->g_grid[grid_x][grid_y]->checked == 0 && grid->g_grid[grid_x][grid_y]->state == 0 ) {
                grid->g_grid[grid_x][grid_y]->nbrs_count = Grid_nbrs(grid, grid->g_grid[grid_x][grid_y]);
                grid->g_grid[grid_x][grid_y]->checked = 1;
                if(Cell_next( grid->g_grid[grid_x][grid_y], rules ) == 1) {
                    tmpAlive->coiArray = addCell1(tmpAlive->coiArray, Cell_new(grid_x,  grid_y), tmpAlive->coiCount);
                    tmpAlive->coiCount++;
                }
            }
        }
    }
}

typedef struct
{
    /** @brief
     *
     */
    CellGrid *tmpAlive;
    Grid *grid;

    RuleSet *rules;
    /** @brief
     *
     */
    int coiCount;

} GridAndTmp;

void *nbrUpdateThread(void *arg)
{
    GridAndTmp *tmp = (GridAndTmp*)arg;

    for(unsigned int i=tmp->tmpAlive->coiCount; i--; ) { /* Add new values to coiArray */
        tmp->grid->coiArray[i] = Cell_new(tmp->tmpAlive->coiArray[i]->row, tmp->tmpAlive->coiArray[i]->col);
        tmp->grid->coiArray[i]->state = 1;
        if(tmp->grid->g_grid[tmp->grid->coiArray[i]->row][tmp->grid->coiArray[i]->col]) {
        tmp->grid->g_grid[tmp->grid->coiArray[i]->row][tmp->grid->coiArray[i]->col]->state = 1;
        tmp->grid->g_grid[tmp->grid->coiArray[i]->row][tmp->grid->coiArray[i]->col]->checked = 0;
        }
        Cell_free(tmp->tmpAlive->coiArray[i]);
    }
    tmp->grid->coiCount = tmp->tmpAlive->coiCount ;

       free(tmp->tmpAlive->coiArray);
       tmp->tmpAlive->coiArray = NULL;
       free(tmp->tmpAlive);
       tmp->tmpAlive = NULL;
    return NULL;
}

void *gridClearThread(void *arg)
{
    Grid *grid = (Grid*)arg;

    for(unsigned int i=grid->rows; i--; ) {
        for(int k=grid->cols; k--; ) {
            if(grid->g_grid[i][k]) {
                grid->g_grid[i][k]->state = 0;
                grid->g_grid[i][k]->checked = 0;
            }
        }
    }


    return NULL;
}

void *gridCheckArrayThread(void *arg)
{
    GridAndTmp *tmp = (GridAndTmp*)arg;
    for(unsigned int i=tmp->grid->coiCount; i--; ) {
    //for(unsigned int i=0;i<grid->coiCount; i+=2 ) {
        tmp->grid->coiArray[i]->nbrs_count = Grid_nbrs( tmp->grid, tmp->grid->coiArray[i] );
        if(Cell_next( tmp->grid->coiArray[i], tmp->rules )) { // Next state is alive.
            tmp->grid->g_grid[tmp->grid->coiArray[i]->row][tmp->grid->coiArray[i]->col]->checked = 1;
            tmp->tmpAlive->coiArray = addCell1( tmp->tmpAlive->coiArray , Cell_new(tmp->grid->coiArray[i]->row, tmp->grid->coiArray[i]->col), tmp->tmpAlive->coiCount );
            tmp->tmpAlive->coiCount++;
        }
        tmp->grid->coiArray[i]->checked = 1;
        Grid_Nbrs_check( tmp->tmpAlive, tmp->grid, tmp->grid->coiArray[i], tmp->rules );
    }
    return NULL;
}

Cell ***Grid_copy_array( Cell ***grid, int rows, int cols )
{

    Cell ***g_grid = (Cell***)calloc(rows+1, sizeof(Cell**));
    for(int i=0; i<rows; i++) {
        g_grid[i] = (Cell**)calloc(cols+1, sizeof(Cell*));
    }

    for(int i=0; i<rows; i++) {
        for(int k=0; k<cols; k++) {
            g_grid[i][k] = Cell_new(i, k);
            g_grid[i][k]->state = grid[i][k]->state;
            g_grid[i][k]->checked  = grid[i][k]->checked;
        }
    }

}

void Grid_next( Grid *grid, RuleSet *rules )
{
    //printf("We have %d cells to check\n", grid->coiCount );
    if(grid) {
        /* This array is used to store tmp values of living cells. */
        CellGrid *tmpAlive = (CellGrid*)calloc(1, sizeof(CellGrid));
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

        end = clock();
        time_t t = (end-start);
        printf("array update time: %d\n", t);

        pthread_t *thread1;
        pthread_create(&thread1, NULL, gridClearThread, grid);
        pthread_join(thread1, NULL);

        Grid_coiEmpty(grid);
        Grid_coiRealloc( grid,  tmpAlive->coiCount );

        GridAndTmp *tmp = (GridAndTmp*)calloc(1, sizeof(GridAndTmp));
        tmp->grid = grid;
        tmp->tmpAlive = tmpAlive;

        pthread_t *thread;
        //object->g_model->is_playing = 1;
        pthread_create(&thread, NULL, nbrUpdateThread, tmp);
        pthread_join(thread, NULL);

    //    grid = Grid_copy_array( grid, grid->rows, grid->cols );
    }

}

void Grid_switch( Grid *grid, int row, int col )
{
    if(grid) {
        switch (grid->g_grid[row][col]->state) {
            case 1: {
                //Cell *c = Cell_new( row, col );
                Grid_coiRem( grid, Cell_new( row, col ) );
                grid->g_grid[row][col]->state = 0;
                break;
            }
            case 0: {
                //Cell *c1 = Cell_new(row,col);
                Grid_coiAdd( grid, Cell_new( row, col ) );
                grid->g_grid[row][col]->state = 1;
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

    if(max_COL > grid->cols) {
        max_COL = cell->col;
    }
    if(max_ROW > grid->rows) {
        max_ROW = cell->row;
    }
    //for(grid_x=max_ROW-1; grid_x>=finalX; grid_x--) {
    //    for(grid_y=max_COL-1; grid_y>=finalY; grid_y--) {

    for(grid_x=finalX;grid_x<max_ROW ; grid_x++) {
        for(grid_y=finalY; grid_y<max_COL; grid_y++) {
            if( grid->g_grid[grid_x][grid_y] && grid->g_grid[grid_x][grid_y]->state == 1 ) {
                if(grid_x != cell->row || grid_y != cell->col) { /* We are not middle cell.*/
                    c++;
                }
            }
        }
    }

    return c;
}

void grid_print( Grid *grid )
{
  printf("Printing array[%d][%d]:\n", grid->rows, grid->cols);
  if(grid->g_grid) {
    for(int i=0; i<grid->rows; i++) {
        printf("r:%d ", i);
        for(int k=0; k<grid->cols; k++) {
            if(grid->g_grid[i][k]){
                printf("[%d]", grid->g_grid[i][k]->state);
            }else {printf("[0]");}
        }
        printf(" \n");
    }
  }
}

/*
int grid_nbrs( int row, int col, int rows, int cols, int **grid )
{
    int c=0;
    int grid_x=row-1, grid_y=col-1;

    for(grid_x=row-1;grid_x<row+2; grid_x++) {
        for(grid_y=col-1; grid_y<col+2; grid_y++) {

            if( grid_x >= 0 && grid_x < rows &&
                grid_y >= 0 && grid_y < cols) {
                    if(grid[grid_x][grid_y] == 1 ) {
                        if(grid_x != row || grid_y != col) {
                            c++;
                        }
                    }

            }

        }
    }

    return c;
}*/
