#include "grid.h"

int **grid_new( int rows, int cols )
{
    //g_print("new grid %d : %d\n", rows, cols);
    int **arr = (int**)calloc(rows, sizeof(int*));
    for(int i=0; i<rows; i++) {
        arr[i] = (int*)calloc(cols, sizeof(int*));
    }
    return arr;
}

void grid_free( int rows, int **arr )
{
    if(arr) {
       for(int i=0; i<rows; i++) {
           free(arr[i]);
       }
       free(arr);
    }
    //arr = NULL;
}

void grid_rand( int rows, int cols, int **arr )
{
    if(arr) {
        for(int i=0; i<rows; i++){
            for(int k=0; k<rows; k++) { arr[i][k] = rand()%2; }
        }
    }
}

void grid_next( int rows, int cols, int **grid, int *live_a, int live_s, int *live_d, int dead_s )
{
    int **tmp_grid = grid_new(rows, cols);
    int k=0, i=0;
    for(i=0; i<rows; i++) {
        for(k=0; k<cols; k++) {
            int nbrs = 0;
            nbrs = grid_nbrs( i, k, rows, cols, grid );
            int life = 0;
            life = cell_next( grid[i][k], nbrs, live_a, live_s, live_d, dead_s );//cell_next_turn(grid[i][k], nbrs);
            tmp_grid[i][k] = life;

        }
    }
    for(i=0; i<rows; i++) {
        for(k=0; k<cols; k++) {
            grid[i][k] = tmp_grid[i][k] ;
        }
    }
    grid_free(rows, tmp_grid);
}

void grid_prev( int x, int y, int **grid, int *live_a, int *live_d )
{

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
