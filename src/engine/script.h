#ifndef SCRIPT_H_INCLUDED
#define SCRIPT_H_INCLUDED

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "position.h"
#include "string.h"

typedef struct
{
    int type;

} script;

void script_update( script *script );

#endif  /*  NODE_H_INCLUDED */
