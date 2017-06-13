#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

#include "node.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define SCRIPT 0
#define NODE   1

typedef struct
{
    int RUNNING;
    int interval;

    int running_scripts;
    int node_count;

    Node **game_grid;

    Node *nodes[];

} GameEngine;

void GameEngine_mainloop( GameEngine *engine );

void GameEngine_runscript( GameEngine *engine, Node *node );

int GameEngine_count( GameEngine *engine, int type );

#endif  /* GAMEENGINE_H_INCLUDED */
