#include "grid.h"

int **grid_new( int x, int y )
{
    int i=0;
    int **arr = (int**)calloc(y, sizeof(int*)); // reallocate user value, BUG leaves some nodes unallocated
    for(i=0; i<y; i++) {
        arr[i] = (int*)calloc(x, sizeof(int*));
    }

    return arr;
}

void grid_rand( int x, int y, int **arr )
{
    int i=0, k=0;
    if(arr) {
        for(i=0; i<y; i++) {
            for(k=0; k<x; k++) { arr[i][k] = rand()%2; }
        }
    }
}

void grid_next( int x, int y, int **grid, int *live_a, int *live_d )
{
    int tmp_grid[y][x];
    int k=0, i=0;
    for(i=0; i<y; i++) {
        for(k=0; k<x; k++) {
            int nbrs = grid_nbrs( k, i, x, y, grid );
            int life = cell_next( grid[i][k], nbrs, live_a, live_d );//cell_next_turn(grid[i][k], nbrs);
            tmp_grid[i][k] = life;
        }
    }
    for(i=0; i<y; i++) {
        for(k=0; k<x; k++) {
            grid[i][k] = tmp_grid[i][k] ;
        }
    }
}

void grid_prev( int x, int y, int **grid, int *live_a, int *live_d )
{

}

void grid_print( int x, int y, int **grid )
{
  int i=0, k=0;

  printf("Printing array:\n");
  if(grid) {
    for(i=0; i<y; i++) {
        g_print("r:%d ", i);
        for(k=0; k<x; k++) { g_print("[%d]", grid[i][k]); }
        g_print("\n");
    }
  }
}

int grid_nbrs( int x, int y, int max_x, int max_y, int **grid )
{
    int c=0;
    int grid_x=x-1, grid_y=y-1;
    //printf("start values x : %d, y : %d : state : %d\n", x, y, grid[y][x]);
    for(grid_y=y-1;grid_y<y+2; grid_y++) {
        for(grid_x=x-1; grid_x<x+2; grid_x++) {//printf("x : %d, y : %d = %d\n", grid_x, grid_y, grid[grid_x][grid_y] );
            if(grid_x >= 0 && grid_x < max_x && grid_y >= 0 && grid_y < max_y) { // set limits for the grid outside cells are dead
                if(grid[grid_y][grid_x] == 1) {
                    if(grid_x == x && grid_y == y) {

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
