#ifndef SCRIPT_H_INCLUDED
#define SCRIPT_H_INCLUDED

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "math/position.h"
#include "string.h"

/** @brief
 *
 */
typedef struct
{
    /** @brief
     *
     */
    int type;

} Script;

/** @brief
 *
 */
void script_update( Script *script );

/** @brief
 *
 */
void script_start( Script *script );

/** @brief
 *
 */
void script_stop( Script *script );

#endif  /*  NODE_H_INCLUDED */
