#ifndef GAMEAREA1_H_INCLUDED
#define GAMEAREA1_H_INCLUDED

#include "node.h"
//#include "../model/gamemodel.h"

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

    /** @brief
     *
     */
//    GameModel *gmodel;

} GameArea1;

/** @brief
 *
 */
GameArea1 *GameArea1_new(int rows, int cols);

/** @brief
 *
 */
void  GameArea1_add( GameArea1 area, Node node );

/** @brief
 *
 */
void GameArea1_rem( GameArea1 area, Node node );

/** @brief
 *
 */
int GameArea_has( GameArea1 area, Node node );
Node *GameArea_get(GameArea1 *area, int row, int col);

#endif  /* GAMEENGINE_H_INCLUDED */
