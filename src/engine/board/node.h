#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../json/objectbase.h"
#include "../math/position.h"
#include "../script.h"

/** @brief
 *
 */
typedef struct
{
    /** @brief
     *    This node is base for all nodes. nodetypes are predefined and have
     *    different properties.
     */
    int type;

    /** @brief
        TODO: not yet implemented.
     *   Each node must have unique id generated from ID-namespace.
     */
    int id;

    /** @brief
     *  Position contains  x and y coordinates in grid.
     */
    Position *pos;

    /** @brief
        TODO: not yet implemented.
     *  Count of all scripts in this Node. SCripts are executed in order of
     *  which they are saved to array.
     */
    int script_count;
    //char *scripts[];

    char *draw_color; /* Color to be used in game board for this node. */

} Node;

/** @brief
 *
 */
Node *Node_new( int row, int col );

/** @brief
 *
 */
void Node_free( Node *node );

/** @brief
 *
 */
void Node_run_scripts( Node *node );

/** @brief
 *
 */
int Node_cmp( Node *orig, Node *toCompare );

/** @brief
 *
 */
ObjectBase* Node_json( Node *node );

#endif  /*  NODE_H_INCLUDED */
