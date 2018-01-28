#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

#include <stdlib.h>

/** @brief
 *
 */
typedef struct
{
    /** @brief
     *
     */
    int x, y;

} Position;

void Position_free( Position *pos );

#endif  /* POSITION_H_INCLUDED */
