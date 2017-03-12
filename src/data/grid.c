#include "grid.h"

Grid *Grid_new( int rows, int cols )
{
    Grid *rtn = (Grid*)calloc(1, sizeof(Grid));
    rtn->rows = rows;
    rtn->cols = cols;

    rtn->grid = (int**)calloc(rtn->rows+1, sizeof(int*));
    for(int i=0; i<rows; i++) {
        rtn->grid[i] = (int*)calloc(rtn->cols+1, sizeof(int));
    }

    rtn->coiCount = -0;
    rtn->coiArray = NULL;

    return rtn;
}

void Grid_free( Grid *grid )
{
    if(grid->grid) {
        for(int i=0; i<grid->rows; i++) {
           free(grid->grid[i]);
           grid->grid[i] = NULL;
       }
       free(grid->grid);
       grid->grid = NULL;
    }
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

            tmp_grid->grid[i][k] = grid->grid[i][k];
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
            grid->grid[i][k] = tmp_grid->grid[i][k];
        }
    }
    Grid_free(tmp_grid); /* Free temporary grid. */
}

void Grid_empty( Grid *grid )
{
    for(int i=0; i<grid->rows; i++) {
        for(int k=0; k<grid->cols; k++) {
            grid->grid[i][k] = 0;
        }
    }
}
int hasCell(Cell **array, size_t size,  Cell *tocheck)
{
    int rtn = 0;

    for(int i=0; i<size; i++) {
        if( array[i]->row == tocheck->row && array[i]->col == tocheck->col ) {
            rtn =1;
            break;
        }
    }

    return rtn;
}

Cell **addCell1( Cell **array, Cell *toAdd, size_t oldSize )
{

        array = realloc(array, (oldSize+1)*sizeof(Cell*));
        //printf("added new cell at: %d\n", oldSize);
        array[oldSize] = toAdd;

    //printf("Adding cell: %d:%d\n", toAdd->row, toAdd->col);
    //Cell *rtn = (Cell*)calloc(newSize+1, sizeof(Cell));
    //Cell **tmparr = (Cell**)calloc(oldSize, sizeof(Cell*));

    return array;
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
    //Cell **tmparr = (Cell**)calloc(size-1, sizeof(Cell*));

    for(int i=0; i<size; i++) {
        //printf("size: %d, %d\n", i, array[i]->x);
        if(array[i]->row == row && array[i]->col == col) {
            remElem(array, i, size);
            array = realloc(array, (size-1)*sizeof(Cell*));
            break;
            //free(array[i]);
            //array[i] == NULL;
            //array[i]->state = 0;
        }
    }

    return array;
}

void remAllCells( Cell **array, size_t size )
{
    for(int i=0; i<size; i++) {

        //if(array[i]->x == x && array[i]->y == y) {
            free(array[i]);
            array[i] = NULL;
        //}
    }

    free(array);
    array = NULL;
}

void Grid_rand( Grid *grid )
{
    /*
    if(grid->coiArray) {
        remAllCells(grid->coiArray, grid->coiCount);
        grid->coiCount = 0;
    }
    */
    if(grid->grid) {
        for(int i=0; i<grid->rows; i++){
            for(int k=0; k<grid->cols; k++) { /* Flip coin for each cell, value is 1 or 0 */
                grid->grid[i][k] = rand()%2;
            }
        }
        for(int i=0; i<grid->rows; i++){
            for(int k=0; k<grid->cols; k++) { /* Flip coin for each cell, value is 1 or 0 */

                if(grid->grid[i][k] == 1) {
                    Cell *c = Cell_new(i, k);
                    c->state = 1;
                    //printf("Add cell at[%d]: %d:%d\n", grid->cellsSize, c.x, c.y );
                    Grid_coiAdd(grid, c);
                    //grid->coiArray = addCell1(grid->coiArray, c, grid->coiCount);
                    //grid->coiCount++;

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

    grid->grid[cell->row][cell->col] = cell->state;
}

void Grid_next( Grid *grid, RuleSet *rules )
{
    printf("We have %d cells to check\n", grid->coiCount );
    if(grid) {
        Grid *tmpGrid = Grid_new(grid->rows, grid->cols);
        Cell **tmpAliveGrid = NULL;
        int k=0, i=0;
        int tmpCellsSize = 0;
        for(i=0; i<grid->coiCount; i++) {
            Cell *c1 = Cell_new(grid->coiArray[i]->row, grid->coiArray[i]->col);
            Cell_set(c1, grid->coiArray[i]->state);
            int nbrs = 0;
            nbrs = grid_nbrs(c1->row, c1->col, grid->rows, grid->cols, grid->grid);
            int life = Cell_next( c1, nbrs,rules ); //cell_next( c1->state, nbrs, rules->live_a, rules->live_s, rules->live_d, rules->dead_s );
            Cell_set(c1, life);
            //printf("Check cell at %d:%d\n", c1->row, c1->col);
            if(life == 1) {
                tmpAliveGrid = addCell1( tmpAliveGrid , c1, tmpCellsSize );
                tmpCellsSize++;
                Grid_addCell( tmpGrid, c1 );
            }
            int c=0;
            int grid_row=c1->row-1, grid_col=c1->col-1;
            for(grid_row=c1->row-1;grid_row<c1->row+2; grid_row++) {
                for(grid_col=c1->col-1; grid_col<c1->col+2; grid_col++) {
                    //if(!hasCell(tmpAliveGrid, tmpCellsSize, c)) {
                        if( grid_row >= 0 && grid_row < grid->rows && /* If row or col is -1 its outside borders */
                            grid_col >= 0 && grid_col < grid->cols) {
                                Cell *c = Cell_new(grid_row, grid_col);
                                if(!hasCell(tmpAliveGrid, tmpCellsSize, c)) {
                                    if(grid->grid[grid_row][grid_col] == 0 ) { //Skip alive cells since they are done in main.
                                        if(grid_row != c1->row && grid_col != c1->col) { /* We are not middle cell.*/
                                            Cell *c = Cell_new(grid_row, grid_col);
                                                int nbrs = 0;
                                                nbrs = grid_nbrs(grid_row, grid_col, grid->rows, grid->cols, grid->grid);
                                                c->state = Cell_next( c, nbrs, rules );

                                                if(c->state == 1) {
                                                    //printf("Adding cell: %d:%d\n", c->row, c->col);
                                                    tmpAliveGrid  = addCell1( tmpAliveGrid , c, tmpCellsSize );
                                                    tmpGrid->grid[c->row][c->col] = 1;
                                                        //printf("cellN[%d][%d]::[%d] had: %d nbrs next state: %d \n",c->row, c->col, c->state, nbrs, life);
                                                    tmpCellsSize++;
                                                }
                                                else {
                                                    tmpGrid->grid[c->row][c->col] = 0;
                                                    Cell_free(c);

                                                }

                                            }


                                        }
                                } else {
                                    Cell_free(c);
                                }

                        }
                    }
                }
                if(c1->state == 0) {
                    Cell_free(c1);
                }
            //printf("--------------------END----------: \n");

        }
        Grid_coiEmpty(grid);
        //printf("realloc COI to %d\n", tmpCellsSize);
        Grid_coiRealloc( grid,  tmpCellsSize );
        //grid->coiArray = realloc(grid->coiArray, (tmpCellsSize)*sizeof(Cell*));
        for(int i=0; i<tmpCellsSize; i++) {
            grid->coiArray[i] = Cell_new(tmpAliveGrid[i]->row, tmpAliveGrid[i]->col);
            grid->coiArray[i]->state = 1;
            //printf("Set cell at : %d - %d - %d:%d\n", i,grid->livingCells[i]->state, grid->livingCells[i]->x, grid->livingCells[i]->y );
        }
        grid->coiCount = tmpCellsSize;

        Grid_empty(grid);
        for(int i=0; i<tmpCellsSize; i++) {
            Cell_free(tmpAliveGrid[i]);
        }

        free(tmpAliveGrid);
        tmpAliveGrid = NULL;

        //grid_print( tmpGrid->rows, tmpGrid->cols, tmpGrid->grid );
        for(i=0; i<grid->rows; i++) {
            memcpy(grid->grid[i], tmpGrid->grid[i], sizeof(int)*grid->cols);
        }
        Grid_free(tmpGrid);
    }
}

void Grid_switch_cell(Grid *grid, int row, int col)
{
    if(grid) {
        printf("Switch cell at x:%d|y:%d :: %d\n", row, col, grid->grid[row][col]);
        if(grid->grid[row][col] == 1) {
            Cell *c = Cell_new(row,col);
            c->state  = 0;
            Grid_coiRem( grid, c );//remCell( grid->livingCells, grid->cellsSize, x, y );
            //grid->coiCount--;
            //g_print("switch cell to 0");
            grid->grid[row][col] = 0;
        } else {
            Cell *c = Cell_new(row,col);
            c->state  = 1;
            Grid_coiAdd( grid, c );
            //grid->coiCount++;
            //g_print("switch cell to 1");
            grid->grid[row][col] = 1;
        }
    }
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
    //printf("start values x : %d, y : %d : state : %d\n", x, y, grid[y][x]);
    /*
    for(grid_x=row-1;grid_x<row+2; grid_x++) {
        for(grid_y=col-1; grid_y<col+2; grid_y++) {
            if(grid_x >= 0 && grid_x < rows && grid_y >= 0 && grid_y < cols) {
                if(grid[grid_x][grid_y] == 1) {
                    if(grid_x == row && grid_y == col) {

                    }
                    else {
                        c++;
                    }

                }
            }
        }
    }
    */
    return c;
}

void grid_print( int x, int y, int **grid )
{
  printf("Printing array:\n");
  if(grid) {
    for(int i=0; i<y; i++) {
        printf("r:%d ", i);
        for(int k=0; k<x; k++) {printf("[%d]", grid[i][k]); }
        printf(" \n");
    }
  }
}
