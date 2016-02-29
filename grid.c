#include "grid.h"

int **grid_init(int x, int y, int **arr)
{
	  printf("allocating x:%d y:%d\n", x, y);
    arr = (int**)calloc(y, sizeof(int*)); // reallocate user value, BUG leaves some nodes unallocated
    // arr = malloc(y * sizeof(int *));
    int i=0;
    for(i=0; i<y; i++) {
        //printf("calloc line: %d\n", i);
        arr[i] = (int*)calloc(x, sizeof(int*));
        //arr[i] = malloc(x * sizeof(int *));
    }
    return arr;
}

int **grid_rand(int x, int y, int **arr)
{
    int i=0, k=0;
    for(i=0; i<y; i++) {
        for(k=0; k<x; k++) {
            int randomval = rand()%2;
            arr[i][k] = randomval;
        }
    }
    return arr;
}

void grid_next(int x, int y, int **grid)
{
    int tmp_grid[y][x];
    int k=0, i=0;
    for(i=0; i<y; i++) {
        for(k=0; k<x; k++) {
            int nbrs = grid_nbrs_count(k, i, x, y, grid);
            int life = cell_next_turn(grid[i][k], nbrs);

            tmp_grid[i][k] = life;
        }
    }

    for(i=0; i<y; i++) {
		//printf("%d: ", i);
        for(k=0; k<x; k++) {
            grid[i][k] = tmp_grid[i][k] ;
            //g_print("[%d]", tmp_grid[i][k]);
        }//g_print("\n");
    }
}

int grid_nbrs_count(int x, int y, int max_x, int max_y, int **grid)
{
    int c=0;
    int grid_x=x-1, grid_y=y-1;
    //printf("start values x : %d, y : %d : state : %d\n", x, y, grid[y][x]);

    for(grid_y=y-1;grid_y<y+2; grid_y++) {
        for(grid_x=x-1; grid_x<x+2; grid_x++) {//printf("x : %d, y : %d = %d\n", grid_x, grid_y, grid[grid_x][grid_y] );
         //printf("round %d\n", grid_x);
            if(grid_x >= 0 && grid_x < max_x && grid_y >= 0 && grid_y < max_y) { // set limits for the grid outside cells are dead

                if(grid[grid_y][grid_x] == 1) {
                    if(grid_x == x && grid_y == y) {

                    }
                    else {
                       // printf("alive found : x : %d, y : %d \n", grid_x, grid_y);
                        c++;
                    }

                }
            }
        }


    }

    return c;
}
