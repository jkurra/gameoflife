#include "gamearea1.h"

Node *GameArea1_get_node( GameArea1 *area, int x, int y )
{
    Node *rtn = NULL;

    for(int i=0; i<area->node_count; i++) {
        if(area->nodes[i]->pos->row == x && area->nodes[i]->pos->col == y) {
            rtn = area->nodes[i];
            break;
        }

    }

    return rtn;
}

void GameArea1_print( GameArea1 *area )
{
    printf("Printing game viewport.\n" );
    for(int i=0; i<area->rows; i++) {
        for(int k=0; k<area->cols; k++) {
            if(GameArea1_get_node(area, i, k) != NULL) {
                printf("[%s]", "E");
            }
            else {
                printf("[%s]", "X");
            }
        }
        printf("\n");
    }
}

Node *GameArea_get(GameArea1 *area, int row, int col)
{
    Node *rtn = NULL;
    for(int i=0; i<area->node_count; i++) {
        if(area->nodes[i]->pos->row == row && area->nodes[i]->pos->col == col ) {
            rtn = area->nodes[i];
        }
    }

    return rtn;
}

GameArea1 *GameArea1_new( int rows, int cols )
{
    printf("Allocating area of size : rows:%d, cols:%d \n", rows, cols);
    GameArea1 *arr = (GameArea1 *)calloc(rows, sizeof(GameArea1));

    /*
     *
     */
    arr->rows = rows;
    arr->cols = cols;

    arr->nodes = (Node**)calloc(0, sizeof(Node*));
    arr->node_count = 0;

    /*for(int i=0; i<rows; i++) {
        arr->nodes[i] = (Node**)calloc(cols, sizeof(Node*));
    }

    for(int i=0; i<rows; i++) {
        for(int k=0; k<cols; k++) {
            arr->nodes[i][k] = NULL;
        }
    }*/

    /*
     *  Allocate space for rows and columns in grid.
     *
    arr->g_array = (Cell***)calloc(rows, sizeof(Cell**));
    for(int i=0; i<rows; i++) {
        arr->g_array[i] = (Cell**)calloc(cols, sizeof(Cell*));
    }

    for(int i=0; i<rows; i++) {
        for(int k=0; k<cols; k++) {
            arr->g_array[i][k] = 0;
        }
    }
    /*
     *  create new cells for allocated spaces in grid and assing cells with default
     *  values which are always 0.
     *
    for(int i=0; i<rows; i++) {
        for(int k=0; k<cols; k++) {
            arr->g_array[i][k] = Cell_new(i, k);
            arr->g_array[i][k]->state   = 0;
            arr->g_array[i][k]->checked = 0;
        }
    }*/
    return arr;
}

void GameArea1_set_nodes( GameArea1 *area, Node **nodes, int node_count )
{
    area->nodes = nodes;
    area->node_count = node_count;
    /*
    area->nodes = (Node**)realloc(area->nodes, (area->node_count+1)*sizeof(Node*));
    area->nodes[area->node_count+1] = node;
    area->node_count++;
    */
    //printf("Added (%d) new node at %d::%d\n", area->node_count, node->pos->row, node->pos->col);
}

int GameArea1_has( GameArea1 *area, Node *node )
{
    int rtn = 0;
    for(int i=0; i<area->node_count; i++) {
        //int r = area->nodes[i]->pos->row;
        //int r2 = node->pos->row ;
        if(area->nodes[i]->pos->row == node->pos->row && area->nodes[i]->pos->col == node->pos->col) {
            rtn = 1;
        }
    }

    return rtn;
}

void GameArea1_clear(GameArea1 *area) {
    for(int i=0; i<area->node_count; i++) {
        free(area->nodes[i]);
        /*if(area->nodes[i]->pos->row == node->pos->row && area->nodes[i]->pos->col == node->pos->col) {
            rtn = 1;
        }*/
    }
    area->nodes = (Node*)realloc(area->nodes, (0)*sizeof(Node));
    area->node_count = 0;
}

void GameArea1_add_node( GameArea1 *area, Node *node )
{
    //printf("Adding node...%d::%d", node->pos->row, node->pos->col);
    //if(!GameArea1_has(area, node)) {

        area->nodes = (Node*)realloc(area->nodes, (area->node_count+1)*sizeof(Node));
        area->nodes[area->node_count] = node;
        area->node_count++;
        //printf("Added new node : %d\n", area->node_count);
        //printf("Added (%d) new node at %d::%d\n", area->node_count, node->pos->row, node->pos->col);
    //}


}

void GameArea1_rem_node( GameArea1 *area, Node *node )
{

}
