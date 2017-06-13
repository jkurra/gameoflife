#include "position"

void Position_new( int x, int y )
{
    Position pos = (Position*)calloc(1, sizeof(Position));

    pos->x = x;
    pos->y = y;

    return pos;
}
