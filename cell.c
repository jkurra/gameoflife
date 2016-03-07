#include "cell.h"

int cell_next_turn( int c_state, int nbrs, int *live_a, int *live_d ) {
    int n_state=0, i=0; // next state of the cell, assumed dead, turned alive if necessary
    if( c_state == 1 ) { // cell is currently alive
      for(i=0; i<sizeof(live_a) / sizeof(int); i++) {
        //printf("lenght: %d\n", sizeof(live_a) / sizeof(int));
        if(nbrs == live_a[i]) {
          //printf("live  value : %d\n", live_a[i]);
          n_state = 1;
        }
      }
    }
    else {
      for(i=0; i<sizeof(live_d) / sizeof(int); i++) {
        if(nbrs == live_d[i]) { n_state = 1; }
      }
    }
    return n_state;
}

int cell_prev_turn( int c_state, int nbrs, int *live_a, int *live_d ) {
    int p_state = 0; // next state of the cell, assumed dead, turned alive if necessary

    return p_state;
}
