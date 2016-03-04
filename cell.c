#include "cell.h"

int cell_next_turn(int c_state, int nbrs) {
    int n_state = 0; // next state of the cell, assumed dead, turned alive if necessary
    if(c_state == 1) { // cell is currently alive
        if(nbrs == 2 || nbrs == 3) {
            n_state = 1;
            
        }
    }
    else {
        if(nbrs == 3) { // this cell has 3 neighbours, it will turn alive
            n_state = 1;
        }
    }
    return n_state;
}

int cell_prev_turn(int c_state, int nbrs) {
    int p_state = 0; // next state of the cell, assumed dead, turned alive if necessary
    if(c_state == 1) { // cell is currently alive
        if(nbrs == 2 || nbrs == 3) {
            p_state = 1;
        }
    }
    else {
        if(nbrs == 3) { // this cell has 3 neighbours, it will turn alive
            p_state = 1;
        }
    }
    return p_state;
}
