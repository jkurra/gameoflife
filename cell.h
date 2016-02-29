#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

#define X_SIZE 0
#define Y_SIZE 0

/*
 * Calculate next state of the cell based on neighbourgs and rules.
 */
int cell_next_turn(int c_state, int nbrs);

/*
 * Calculate previous state of the cell based on neighbourgs and rules.
 */
int cell_prev_turn(int c_state, int nbrs);

#endif
