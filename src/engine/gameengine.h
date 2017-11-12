#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "board.h"
#include "../model/gamemodel.h"


/* */
#define SCRIPT 0
#define NODE   1

/** @brief
 *
 */
typedef struct
{
    /** @brief
     *
     */
    int RUNNING;
    /** @brief
     *
     */
    int interval;
    /** @brief
     *
     */
    pthread_t *gameThread;
    /** @brief
     *
     */
    int running_scripts;

    /** @brief
     *
     */

    GameModel *gmodel;
    Board *area;

} GameEngine;

/** @brief
 *
 */
void GameEngine_mainloop( GameEngine *engine );

/** @brief
 *
 */
void GameEngine_step( GameEngine *engine );

/** @brief
 *
 */
void GameEngine_runscript( GameEngine *engine, Node *node );

/** @brief
 *
 */
int GameEngine_count( GameEngine *engine, int type );

#endif  /* GAMEENGINE_H_INCLUDED */
