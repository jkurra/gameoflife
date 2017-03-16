#include "grid.h"

/** @brief Print two dimensional array to console.
 *
 */
void grid_print(Grid *grid );

Grid *Grid_new( int rows, int cols )
{
    Grid *rtn = (Grid*)calloc(1, sizeof(Grid));
    rtn->rows = rows;
    rtn->cols = cols;

    rtn->g_grid = (Cell***)calloc(rtn->rows+1, sizeof(Cell**));
    for(int i=0; i<rows; i++) {
        rtn->g_grid[i] = (Cell**)calloc(rtn->cols+1, sizeof(Cell*));
    }

    for(int i=0; i<rtn->rows; i++) {
        for(int k=0; k<rtn->cols; k++) {
            rtn->g_grid[i][k] = Cell_new(i, k);
            rtn->g_grid[i][k]->checked = 0;
        }
    }

    rtn->coiCount = -0;
    rtn->coiArray = NULL;

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

       free(grid->g_grid);
       grid->g_grid = NULL;
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
    for(int i=0; i<grid->coiCount; i++) {
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
            for(int i=0; i<grid->coiCount; i++) {
                free(grid->coiArray[i]);
                grid->coiArray[i] = NULL;
            }

            grid->coiCount = 0;
        }
    }
}

void Grid_resize( Grid *grid, int new_rows, int new_cols )
{
    /* Create temporary grid for copying the current game */
    Grid *tmp_grid = Grid_new(grid->rows, grid->cols);
    /* Copy current nodes to tmp array */
    for(int i=0; i<grid->rows; i++) {

        for(int k=0; k<grid->cols; k++) {

            tmp_grid->g_grid[i][k] = grid->g_grid[i][k];
        }
    }
    /* Free current grid and allocate new one. */
    Grid_free(grid);
    grid = Grid_new(new_rows, new_cols);
    //g_print("Create grid size [%d][%d]:[%d][%d]", new_rows, new_cols,tmp_grid->rows, tmp_grid->cols );
    /*
        Copy existing cells to new grid, if new  grid is smaller than previous,
        loop will break when boundaries of the new grid are reached.
    */
    for(int i=0; i<grid->rows; i++) {
        if(i>=tmp_grid->rows || i>=grid->rows) { break; }
        for(int k=0; k<grid->cols; k++) {
            if(i>=tmp_grid->cols || i>=grid->cols) { break; }
            /*if(tmp_grid->grid[i][k] == 1) {
                g_print("found live cell at: %d:%d", i, k);
            }*/
            grid->g_grid[i][k] = tmp_grid->g_grid[i][k];
        }
    }
    Grid_free(tmp_grid); /* Free temporary grid. */
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
        for(int i=0; i<grid->rows; i++){
            for(int k=0; k<grid->cols; k++) { /* Flip coin for each cell, value is 1 or 0 */
                int rval = rand()%2;
                grid->g_grid[i][k]->state = rval;
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

void Grid_prev( Grid *grid, RuleSet *rules )
{

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

void Grid_next( Grid *grid, RuleSet *rules )
{
    //printf("We have %d cells to check\n", grid->coiCount );
    if(grid) {
        //Cell *tmp_array;
        CellGrid *tmpAlive = (CellGrid*)calloc(1, sizeof(CellGrid));
        CellGrid *wasChecked = (CellGrid*)calloc(1, sizeof(CellGrid));
        for(int i=0; i<grid->coiCount; i++) {
            Cell *c = Cell_new( grid->coiArray[i]->row, grid->coiArray[i]->col );
            //grid_print(grid);
            c->state = 1;
            c->nbrs_count = Grid_nbrs( grid, c );
            //printf("nbrs: %d\n", Grid_nbrs( grid->g_grid, c ));
            int life = Cell_next( c, rules );
            //printf("%s\n", );
            if(life == 1) { // Next state is alive.
                grid->g_grid[c->row][c->col]->checked = 1;
                tmpAlive->coiArray = addCell1( tmpAlive->coiArray , Cell_new(c->row, c->col), tmpAlive->coiCount );
                tmpAlive->coiCount++;
            }
            grid->coiArray[i]->checked = 1; /* Mark as checked.  */
            int grid_x=c->row-1, grid_y=c->col-1;

            for(grid_x=c->row-1;grid_x<c->row+2; grid_x++) {
                for(grid_y=c->col-1; grid_y<c->col+2; grid_y++) {

                    if( grid_x >= 0 && grid_x < grid->rows && /* If row or col is -1 its outside borders */
                        grid_y >= 0 && grid_y < grid->cols) {
                            if(grid->g_grid[grid_x][grid_y]->state == 0 && grid->g_grid[grid_x][grid_y]->checked == 0) {
                                Cell *c1 = Cell_new( grid_x,  grid_y);
                                c1->state = 0;
                                c1->nbrs_count = Grid_nbrs( grid, c1 );
                                if( Cell_next( c1, rules ) == 1 ) {
                                    tmpAlive->coiArray = addCell1( tmpAlive->coiArray, c1, tmpAlive->coiCount );
                                    tmpAlive->coiCount++;

                                    wasChecked->coiArray = addCell1( wasChecked->coiArray, Cell_new( grid_x,  grid_y), wasChecked->coiCount );
                                    wasChecked->coiCount++;
                                    grid->g_grid[grid_x][grid_y]->checked = 1;
                                }
                                else {
                                    Cell_free(c1);
                                }
                            }
                        }
                    }
                }
                Cell_free(c);
            }

        Grid_coiEmpty(grid);
        Grid_coiRealloc( grid,  tmpAlive->coiCount );
        //grid->coiArray = realloc(grid->coiArray, (tmpCellsSize)*sizeof(Cell*));
        for(int i=0; i<tmpAlive->coiCount; i++) {
            grid->coiArray[i] = Cell_new(tmpAlive->coiArray[i]->row, tmpAlive->coiArray[i]->col);
            grid->coiArray[i]->state = 1;
            //printf("Set cell at : %d - %d - %d:%d\n", i,grid->livingCells[i]->state, grid->livingCells[i]->x, grid->livingCells[i]->y );
        }

        grid->coiCount = tmpAlive->coiCount ;
        Grid_empty(grid);

        for(int i=0; i<tmpAlive->coiCount; i++) {
            //grid->g_grid[grid->coiArray[i]->row][grid->coiArray[i]->col] = Cell_new(tmpAlive->coiArray[i]->row, tmpAlive->coiArray[i]->col);
            grid->g_grid[grid->coiArray[i]->row][grid->coiArray[i]->col]->state = 1;
            grid->g_grid[grid->coiArray[i]->row][grid->coiArray[i]->col]->checked = 0;
        }

        for(int i=0; i<wasChecked->coiCount; i++) {
            Cell_free(wasChecked->coiArray[i]);
        }
        free(wasChecked->coiArray);
        wasChecked->coiArray = NULL;
        free(wasChecked);
        wasChecked = NULL;

        for(int i=0; i<tmpAlive->coiCount; i++) {
            Cell_free(tmpAlive->coiArray[i]);
        }
        free(tmpAlive->coiArray);
        tmpAlive->coiArray = NULL;
        free(tmpAlive);
        tmpAlive = NULL;
    }
    //g//rid_print( grid );
}

void Grid_switch_cell( Grid *grid, int row, int col )
{
    if(grid) {
        switch (grid->g_grid[row][col]->state) {
            case 1: {
                Cell *c = Cell_new( row, col );
                Grid_coiRem( grid, c );
                grid->g_grid[row][col]->state = 0;
                Cell_free(c);
                break;
            }
            case 0: {
                Cell *c1 = Cell_new(row,col);
                Grid_coiAdd( grid, c1 );
                grid->g_grid[row][col]->state = 1;
                Cell_free(c1);
                break;
            }
            default:
                break;
        }
    }
}

int Grid_nbrs( Grid *grid, Cell *cell) //int row, int col, int rows, int cols, int **grid )
{
    int c=0;
    int grid_x=cell->row-1, grid_y=cell->col-1;
    //grid_print(grid);
    //printf("Cell at : %d:%d\n", cell->row, cell->col );
    for(grid_x=cell->row-1;grid_x<cell->row+2; grid_x++) {
        for(grid_y=cell->col-1; grid_y<cell->col+2; grid_y++) {

            if( grid_x >= 0 && grid_x < grid->rows && /* If row or col is -1 its outside borders */
                grid_y >= 0 && grid_y < grid->cols) {
                    if(grid->g_grid[grid_x][grid_y] != NULL) {
                        //printf("Cell nbr : %d\n", grid->g_grid[grid_x][grid_y]->state );
                        if( grid->g_grid[grid_x][grid_y]->state == 1 ) {
                            if(grid_x != cell->row || grid_y != cell->col) { /* We are not middle cell.*/
                            //    printf("increase c\n" );
                                c++;
                            }
                        }
                    }
            }

        }
    }

    return c;
}

int grid_nbrs( int row, int col, int rows, int cols, int **grid )
{
    int c=0;
    int grid_x=row-1, grid_y=col-1;

    for(grid_x=row-1;grid_x<row+2; grid_x++) {
        for(grid_y=col-1; grid_y<col+2; grid_y++) {

            if( grid_x >= 0 && grid_x < rows && /* If row or col is -1 its outside borders */
                grid_y >= 0 && grid_y < cols) {
                    if(grid[grid_x][grid_y] == 1 ) {
                        if(grid_x != row || grid_y != col) { /* We are not middle cell.*/
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
