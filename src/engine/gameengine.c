#include "gameengine.h"

void GameEngine_mainloop( GameEngine *engine )
{
    if(engine) {

        while(1) {
            for(int i=0; i<engine->node_count; i++) {
                GameEngine_runscript(engine, engine->nodes[i]);
            }
        }
    }
}

void GameEngine_runscript( GameEngine *engine, Node *node )
{

}
