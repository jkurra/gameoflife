#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "node.h"

/** @brief Structure for Board which can hold Nodes.
 *
 *  Board is basically a two dimensional array, which has nodes and empty places.
 *  When a node is added, it will occupy certain position in x and y coordinates.
 *  It is possible to add more than one Node in same coordinates (TODO: implement
 *  when basic functionality is in place). Each node also has a unique ID which
 *  can be used to identify particular node. Nodes can be searched using ID (In
 *  which case user must keep track of each id themselves) or x and y coordinates
 *  (In this case return can be more than one cell).
 */
typedef struct
{
    /** @brief Rows and columns tell basic dimension of the board.
     *
     *  Dimensions represent basic viewport in a 2D grid. Rows are same as x
     *  coordinates and columns are same as y coordinates. Changing either one
     *  affects the other as well. Negative values are not allowed (zero values
     *  may be necessary for some special cases).
     */
    int rows, cols;

    /** @brief Path to savefile of the original board.
     *
     *  Path to file containing all Nodes and their positions in the original
     *  Board that has not taken been updated once. This makes it easy to test
     *  how different configurations quickly.
     */
    char *orig_save;

    /** @brief Contains all nodes within board.
     *
     *  Nodes hold x and y coordinates in their strucure. Therefore it is only
     *  necessary to hold information about assigned nodes in board. all coordinates
     *  points that are not found in this array are assumed empty and Therefore
     *  ignored.
     */
    Node **nodes;

    /** @brief Holds count of nodes within board.
     *
     *  Because there must be a consistent and safe way of accessing "nodes" array,
     *  it is necessary to keep track of how many nodes are in it. If nodes are
     *  added or removed, this count must be updated. It should be noted that
     *  all access to nodes should be done using safe functions in this class.
     */
    int node_count;

} Board;

/** @brief Returns freshly allocated Board.
 *
 *  Allocates memory for Board and saves given dimensions.
 */
Board *Board_new( int rows, int cols );

/** @brief Free board and all members.
 *
 *  Free all dynamically allocated variables in Board.
 */
void Board_free( Board *board );

/** @brief All nodes to original positions.
 *
 *  TODO: not yet implemented.
 *  Resets all nodes to positions read from the orig_save file.
 */
void Board_reset( Board *board );

/** @brief Resizes board using given dimensions.
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
void Board_remove( Board *board, int id );

/** @brief
 *
 */
void Board_remove_at( Board *board, int x, int y );

/** @brief Get Node with given id.
 *
 */
Node *Board_get( Board *board, int x, int y );

/** @brief Check if board contains given node.
 *
 */
int Board_has( Board *board, Node *node );

/** @brief Full json representation of the board.
 *
 */
char *Board_json( Board *board );

#endif  /* GAMEENGINE_H_INCLUDED */
