#include "cell.h"

Cell *Cell_new( int row, int col )
{
    Cell *rtn = (Cell*)calloc(1, sizeof(Cell));

    rtn->row = row;
    rtn->col = col;
    rtn->nbrs_count = 0;
    rtn->state = 0;
    rtn->checked = 0;

    return rtn;
}

void Cell_free(Cell *cell)
{
    if(cell) {
        free(cell);
        cell = NULL;
    }
}

int Cell_prev( Cell *cell, RuleSet *rules )
{
    int n_state = 0;
    return n_state;
}

int Cell_next( Cell *cell, RuleSet *rules )
{
    int i=0, n_state = 0; // next state of the cell, assumed dead, turned alive if necessary
    if(cell) {
        if( cell->state == 1 ) { // cell is currently alive
            for(i=0; i<rules->live_s; i++) {
                if(cell->nbrs_count == rules->live_a[i]) { n_state = 1; }
            }
        }
        else {
            for(i=0; i<rules->dead_s; i++) {
                if(cell->nbrs_count == rules->live_d[i]) { n_state = 1; }
            }
        }
    }

    return n_state;
}
