#include "board.h"

Board *Board_new( int rows, int cols )
{
    Board *board = NULL;

    /*
     *
     */
    board = (Board*)calloc(rows, sizeof(Board));

    /*
     *
     */
    board->rows = rows;
    board->cols = cols;

    /*
     *
     */
    board->nodes = (Node**)calloc(0, sizeof(Node*));
    board->node_count = 0;

    return board;
}

void Board_free( Board *board )
{
    /*
     *
     */
    for(int i=0; i<board->node_count; i++) {
        free(board->nodes[i]);
        board->nodes[i] = NULL;
    }

    /*
     *
     */
    free(board);
    board = NULL;
}

void Board_add( Board *board, Node *node )
{    printf("Adding node..\n");
    board->nodes = (Node*)realloc(board->nodes, (board->node_count+1)*sizeof(Node));
    board->nodes[board->node_count] = node;
    board->node_count++;
    printf("Node added...\n");
}

void Board_remove( Board *board, int id )
{
    for(int i=0; i<board->node_count; i++) {
        if(board->nodes[i]->id == id) {

        }
    }
}

void Board_remove_at( Board *board, int x, int y )
{
    for(int i=0; i<board->node_count; i++) {
        if(board->nodes[i]->pos->row == x && board->nodes[i]->pos->col == y ) {

        }
    }
}

int Board_has( Board *board, Node *node )
{
    int rtn = 0;

    for(int i=0; i<board->node_count; i++) {
        if(board->nodes[i]->pos->row == node->pos->row && board->nodes[i]->pos->col == node->pos->col ) {// TODO: implement id based identification. if(board->nodes[i]->id == node->id) {
            rtn = 1;
            break;
        }
    }

    return rtn;
}

Node *Board_get( Board *board, int x, int y )
{
    Node *rtn = NULL;
    for(int i=0; i<board->node_count; i++) {
        if(board->nodes[i]->pos->row == x && board->nodes[i]->pos->col == y ) {
            rtn = board->nodes[i];
        }
    }
    return rtn;

}