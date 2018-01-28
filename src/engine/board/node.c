#include "node.h"

Node *Node_new( int row, int col )
{
    Node *node = (Node*)calloc(1, sizeof(Node));

    node->pos = (Position*)calloc(1, sizeof(Position));
    node->type = -1;
    node->script_count = 0;

    node->pos->x = row;
    node->pos->y = col;
    node->draw_color = (GdkRGBA *)calloc(1, sizeof(GdkRGBA));
    gdk_rgba_parse(node->draw_color, "rgb(245,121,0)");

    return node;
}

void Node_free( Node *node ) {

    Position_free(node->pos);

    free(node);
    node = NULL;

}

int Node_cmp( Node *orig, Node *toCompare )
{
    int rtn = 0;
    /*if(orig->pos->x != toCompare->pos->x || orig->pos->y != toCompare->pos->y) {
        rtn = 1;
    }*/

    return rtn;
}

void Node_update( Node *node )
{
    printf("Updating script...\n" );
    /*
    for(int i=0; i<node->script_count; i++) {
    //    Node_run_script()
}*/
}

void Node_set_pos( Node *node, Position *pos )
{
    free(node->pos);
    node->pos = NULL;
    node->pos = pos;
}

void Node_run_scripts( Node *node )
{
    //printf("Running scripts in node...\n");
}
