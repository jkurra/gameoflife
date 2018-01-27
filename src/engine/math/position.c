#include "position.h"

Position *Position_new( int x, int y )
{
    Position *pos = (Position*)calloc(1, sizeof(Position));

    pos->row = x;
    pos->col = y;

    return pos;
}

void Position_free( Position *pos )
{
    free(pos);
    pos = NULL;
}
