#include "node.h"

Node *Node_new( int row, int col )
{
    Node *node = (Node*)calloc(1, sizeof(Node));

    node->id = -1;
    node->pos = (Position*)calloc(1, sizeof(Position));
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

char *Node_json( Node *node )
{
    JsonObject *nodeObject = json_parse(NULL);

    char *type = (char*) calloc(10, sizeof(char*));
    char *id = (char*) calloc(10, sizeof(char*));
    char *script_count = (char*) calloc(10, sizeof(char*));
    char *x = (char*) calloc(10, sizeof(char*));
    char *y = (char*) calloc(10, sizeof(char*));

    sprintf(id,"%d", node->id);

    sprintf(x,"%d", node->pos->x);
    sprintf(y,"%d", node->pos->y);
/*    sprintf(script_count,"%d", node->script_count);
*/

    //JsonKeypair interval = json_keypair_create( "interval", iv);
    json_add_value(nodeObject, json_keypair_create("id", id));
    json_add_value(nodeObject, json_keypair_create("x", x));
    json_add_value(nodeObject, json_keypair_create("y", y));


    //json_add(engineObject, json_tok());
    return nodeObject->main_object;
}
