#include "cell.h"

int cell_next( int c_state, int nbrs, int live_a[], int live_s, int live_d[], int dead_s )
{
    int i=0, n_state = 0; // next state of the cell, assumed dead, turned alive if necessary

    if( c_state == 1 ) { // cell is currently alive
        for(i=0; i<live_s; i++) {
            if(nbrs == live_a[i]) { n_state = 1; }
        }
    }
    else {
        for(i=0; i<dead_s; i++) {
            if(nbrs == live_d[i]) { n_state = 1; }
        }
    }
    return n_state;
}

int cell_prev( int c_state, int nbrs, int *live_a, int *live_d )
{
    int p_state = 0; // next state of the cell, assumed dead, turned alive if necessary

    return p_state;
}
