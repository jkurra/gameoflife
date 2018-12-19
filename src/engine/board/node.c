#include "node.h"

Node *Node_new( int row, int col )
{
    Node *node = (Node*)calloc(1, sizeof(Node));

    node->id = -1;
    node->pos = Position_new(row, col);//(Position*)calloc(1, sizeof(Position));
    node->type = -1;
    node->script_count = 0;

    node->pos->x = row;
    node->pos->y = col;
    //node->draw_color = //(GdkRGBA *)calloc(1, sizeof(GdkRGBA));
    //gdk_rgba_parse(node->draw_color, "rgb(245,121,0)");

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

void Node_set_pos( Node *node, Position *new_pos )
{
    /* Free current position from memory. */
    free(node->pos);
    node->pos = NULL;
    /* Replace position in node with new position */
    node->pos = new_pos;
}

void Node_run_scripts( Node *node )
{
    //printf("Running scripts in node...\n");
    /* TODO: run each script in node.
    for(int i=0; i<node->script_count; i++) {
    //    Node_run_script()
    }
    */
}

ObjectBase *Node_json( Node *node )
{
    ObjectBase *node_obj = ObjectBase_new();

    char *id   = (char*) calloc(10, sizeof(char*));
    char *type = (char*) calloc(10, sizeof(char*));
    char *x    = (char*) calloc(10, sizeof(char*));
    char *y    = (char*) calloc(10, sizeof(char*));

    sprintf(id, "%d", node->id);
    sprintf(type, "%d", node->type);
    sprintf(x, "%d", node->pos->x);
    sprintf(y, "%d", node->pos->y);

    ObjectBase_add(node_obj, JsonValue_new_string("id", id));
    ObjectBase_add(node_obj, JsonValue_new_string("type", type));
    ObjectBase_add(node_obj, JsonValue_new_string("x", x));
    ObjectBase_add(node_obj, JsonValue_new_string("y", y));

    return node_obj;
}
