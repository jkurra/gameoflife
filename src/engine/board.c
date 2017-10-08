#include "board.h"

Board *Board_new( int rows, int cols )
{
    Board *arr = NULL;

    /*
     *
     */
    arr = (Board*)calloc(rows, sizeof(Board));

    /*
     *
     */
    arr->rows = rows;
    arr->cols = cols;

    /*
     *
     */
    arr->nodes = (Node**)calloc(0, sizeof(Node*));
    arr->node_count = 0;

    return arr;
}
