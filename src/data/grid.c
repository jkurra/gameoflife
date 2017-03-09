#include "grid.h"

Grid *Grid_new( int rows, int cols )
{
    Grid *rtn = (Grid*)calloc(1, sizeof(Grid));
    rtn->rows = rows;
    rtn->cols = cols;

    rtn->grid = (int**)calloc(rtn->rows+1, sizeof(int*));
    for(int i=0; i<rows; i++) {
        rtn->grid[i] = (int*)calloc(rtn->cols+1, sizeof(int));
        /*for(int k=0; k<rtn->cols; k++) {
            rtn->grid[i][k] = 0;
        }*/
        //rtn->grid[i] = 0;
    }

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
            if(tmp_grid->grid[i][k] == 1) {
                g_print("found live cell at: %d:%d", i, k);
            }
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

void Grid_rand( Grid *grid )
{
    if(grid->grid) {
        for(int i=0; i<grid->rows; i++){
            for(int k=0; k<grid->cols; k++) { /* Flip coin for each cell, value is 1 or 0 */
                grid->grid[i][k] = rand()%2;
            }
        }
    }
}

void Grid_prev( Grid *grid, RuleSet *rules )
{

}

void Grid_next( Grid *grid, RuleSet *rules )
{

    if(grid) {
        Grid *tmpGrid = Grid_new(grid->rows, grid->cols);
        int k=0, i=0;
        for(i=0; i<grid->rows; i++) {
            for(k=0; k<grid->cols; k++) {
                int nbrs = 0;
                nbrs = grid_nbrs(i, k, grid->rows, grid->cols, grid->grid);
                //g_print("cell nbrs %d\n", nbrs);
                int life = 0;
                //g_print("rules: d:%d|a:%d", rules->live_d[0], rules->live_a[0]);
                life = cell_next( grid->grid[i][k], nbrs, rules->live_a, rules->live_s, rules->live_d, rules->dead_s );//cell_next_turn(grid[i][k], nbrs);
                //life = cell_next( grid[i][k], nbrs, live_a, live_s, live_d, dead_s );
                //g_print("cell nbrs %d[%d]\n", nbrs, life);
                tmpGrid->grid[i][k] = life;

            }

        }
        for(i=0; i<grid->rows; i++) {
            for(k=0; k<grid->cols; k++) {
                grid->grid[i][k] = tmpGrid->grid[i][k];
            }
        }
        Grid_free(tmpGrid);
    }
}

void Grid_switch_cell(Grid *grid, int x, int y)
{
    if(grid) {
        if(grid->grid[y][x] == 1) {
            //g_print("switch cell to 0");
            grid->grid[y][x] = 0;
        } else {
            //g_print("switch cell to 1");
            grid->grid[y][x] = 1;
        }
    }
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

int grid_nbrs( int row, int col, int rows, int cols, int **grid )
{
    int c=0;
    int grid_x=row-1, grid_y=col-1;
    //printf("start values x : %d, y : %d : state : %d\n", x, y, grid[y][x]);
    for(grid_x=row-1;grid_x<row+2; grid_x++) {
        for(grid_y=col-1; grid_y<col+2; grid_y++) {//printf("x : %d, y : %d = %d\n", grid_x, grid_y, grid[grid_x][grid_y] );
            if(grid_x >= 0 && grid_x < rows && grid_y >= 0 && grid_y < cols) { // set limits for the grid outside cells are dead
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

    return c;
}
