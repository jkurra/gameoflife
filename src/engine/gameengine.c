#include "gameengine.h"

void *engineThread(void *arg)
{
    GameEngine *engine = (GameEngine*)arg;

    while(engine->RUNNING) {
        for(int i=0; i<engine->board->node_count; i++) {
            Node_run_scripts(engine->board->nodes[i]);
        }

        usleep(engine->interval);
    }
}

void GameEngine_mainloop( GameEngine *engine )
{
    if(!engine) {
    //    ViewObject *rtn = (ViewObject*)calloc(1, sizeof(ViewObject));
        printf("reallocation of the engine \n");
        engine = (GameEngine*)calloc(1, sizeof(GameEngine));
        //engine->node_count = 0;
        engine->RUNNING = 1;
        engine->interval = 10000;
        engine->board = Board_new(10,10);
        engine->bmodel = BModel_new();

    }

    if(engine) {
        pthread_create(&engine->gameThread, NULL, engineThread, engine);
    }
}

void GameEngine_runscript( GameEngine *engine, Node *node )
{

}

void GameEngine_update_view( GameEngine *engine )
{

}

int GameEngine_count( GameEngine *engine, int type )
{
    int rtn = 0;

    if(engine ){
        switch (type) {
            case NODE:
                //rtn = engine->node_count;
                break;
            case SCRIPT:
                //rtn = engine->running_scripts;
                break;
            default:
                break;
        }
    }

    return rtn;
}

char *GameEngine_json( GameEngine *engine )
{
    JsonObject *engineObject = json_parse(NULL);

    char *iv = (char*) calloc(10, sizeof(char*));
/*    char *cols =   (char*) calloc(10, sizeof(char*));
    char *t_time = (char*) calloc(10, sizeof(char*));
    char *vis =    (char*) calloc(10, sizeof(char*));*/

    sprintf(iv,"%d",engine->interval);

    //JsonKeypair interval = json_keypair_create( "interval", iv);
	json_add_value(engineObject, json_keypair_create( "interval", iv), 0);
    json_add_object(engineObject, json_parse(Board_json(engine->board)), 0);
    json_add_object(engineObject, json_parse(BModel_json(engine->bmodel)), 0);
    //json_add(engineObject, json_tok());
    return engineObject->main_object;
}
