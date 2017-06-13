#include "gameengine.h"

void Node_update( Node *node )
{

}

void Node_set_pos( Node *node, Position *pos )
{
    free(node->pos);
    node->pos = NULL;
    node->pos = pos;
}

void Node_run_script( Node *node, script *script )
{
    script_start(script);
    script_update();
}
