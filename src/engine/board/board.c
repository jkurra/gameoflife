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

void Board_resize( Board *board, int newX, int newY )
{
    board->rows = newX;
    board->cols = newY;
}

void Board_add( Board *board, Node *node )
{   // printf("Adding node..\n");
    board->nodes = (Node*)realloc(board->nodes, (board->node_count+1)*sizeof(Node));
    board->nodes[board->node_count] = node;
    board->node_count++;
    //printf("Node added...\n");
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
        if(board->nodes[i]->pos->x == x && board->nodes[i]->pos->y == y ) {

        }
    }
}

int Board_has( Board *board, Node *node )
{
    int rtn = 0;

    for(int i=0; i<board->node_count; i++) {
        if(board->nodes[i]->pos->x == node->pos->x && board->nodes[i]->pos->y == node->pos->y ) {// TODO: implement id based identification. if(board->nodes[i]->id == node->id) {
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
        if(board->nodes[i]->pos->x == x && board->nodes[i]->pos->y == y ) {
            rtn = board->nodes[i];
        }
    }

    return rtn;
}

char *Board_json( Board *board )
{
/*    JsonObject *boardObject = json_parse(NULL);

    char *cols = (char*) calloc(10, sizeof(char*));
    char *rows = (char*) calloc(10, sizeof(char*));

    sprintf(rows,"%d",board->rows);
    sprintf(cols,"%d",board->cols);

    //JsonKeypair interval = json_keypair_create( "interval", iv);
    json_add_value(boardObject, json_keypair_create("rows", rows));
    json_add_value(boardObject, json_keypair_create("cols", cols));

    for(int i=0; i<board->node_count; i++) {
        //JsonObject *obj = json_parse(Node_json(board->nodes[i]));
        json_add_object(boardObject, json_parse(Node_json(board->nodes[i])));
    }
    //json_add(engineObject, json_tok());
    return boardObject->main_object;*/
}
