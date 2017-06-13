#include "gameengine.h"

void GameEngine_mainloop( GameEngine *engine )
{
    if(engine) {
        while(engine->RUNNING) {
            for(int i=0; i<engine->node_count; i++) {
                GameEngine_runscript(engine, engine->nodes[i]);
            }

            usleep(engine->interval);
        }
    }
}

void GameEngine_runscript( GameEngine *engine, Node *node )
{

}

int GameEngine_count( GameEngine *engine, int type )
{
    int rtn = 0;

    if(engine ){
        switch (type) {
            case NODE:
                rtn = engine->node_count;
                break;
            case SCRIPT:
                rtn = engine->running_scripts;
                break;
            default:
                break;
        }
    }

    return rtn;
}
