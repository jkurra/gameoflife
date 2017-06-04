#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef struct
{
    int type;

    char *scripts[];

} Node;

void Node_update( Node *node );

#endif  /*  NODE_H_INCLUDED */
