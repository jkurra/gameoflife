#ifndef GAMEAREA1_H_INCLUDED
#define GAMEAREA1_H_INCLUDED

#include "node.h"

/** @brief
 *
 */
typedef struct
{
    /** @brief
     *
     */
    int rows, cols;

    /** @brief
     *
     */
    Node **nodes;

    /** @brief
     *
     */
    int node_count;

} Board;

/** @brief
 *
 */
Board *Board_new(int rows, int cols);

/** @brief
 *
 */
void Board_free( Board *board );

/** @brief
 *
 */
void Board_resize( Board *board, int newX, int newY );

/** @brief
 *
 */
void Board_add( Board *board, Node *node );

/** @brief
 *
 */
void Board_rem( Board *board, Node *node );

/** @brief
 *
 */
Node *Board_get( Board *board, Node *node );

/** @brief
 *
 */
int Board_has( Board *board, Node *node );

#endif  /* GAMEENGINE_H_INCLUDED */
