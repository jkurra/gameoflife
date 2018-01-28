#include "gameengine.h"

void *engineThread(void *arg)
{
    GameEngine *engine = (GameEngine*)arg;
    //add checks as necessary.
    if(engine->RUNNING) {
        /*printf("Engine running.\n");
        for(int i=0; i<engine->gmodel->grid->lArray->base.count; i++) {
            //printf("Node created.\n");
            Node *n = Node_new(CellArray_get(engine->gmodel->grid->lArray, i)->row, CellArray_get(engine->gmodel->grid->lArray, i)->col);
            //printf("Node created.\n");
            Board_add(engine->area, n);
            //engine->area->nodes[i]
        }*/
    }
    while(engine->RUNNING) {
        for(int i=0; i<engine->board->node_count; i++) {
            Node_run_scripts(engine->board->nodes[i]);
        }

/*
        for(int i=0; i<engine->gmodel->grid->lArray->base.count; i++) {

            Node *n = Node_new(CellArray_get(engine->gmodel->grid->lArray, i)->row, CellArray_get(engine->gmodel->grid->lArray, i)->col);
            //if(!GameArea1_has(engine->area, n)) {
            if(!Board_has( engine->area, n )) {
                Board_add(engine->area, n);
            }
            //}
            //engine->area->nodes[i]
        }*/

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
        //GameArea1_print(engine->area );

        /*
        if(engine->RUNNING) {
            printf("Engine running.\n");
        }
        while(engine->RUNNING) {
            for(int i=0; i<engine->node_count; i++) {
                printf("Updating scripts: %d\n", i );
                GameEngine_runscript(engine, engine->nodes[i]);
            }
            GameEngine_update_view(engine);

            usleep(engine->interval);
        }*/
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

    char *iv =   (char*) calloc(10, sizeof(char*));
/*    char *cols =   (char*) calloc(10, sizeof(char*));
    char *t_time = (char*) calloc(10, sizeof(char*));
    char *vis =    (char*) calloc(10, sizeof(char*));*/

    sprintf(iv,"%d",engine->interval);

    //JsonKeypair interval = json_keypair_create( "interval", iv);
	json_add_value(engineObject, json_keypair_create( "interval", iv));
    json_add_object(engineObject, json_parse(Board_json(engine->board)));
    json_add_object(engineObject, json_parse(BModel_json(engine->bmodel)));
    //json_add(engineObject, json_tok());
    return engineObject->main_object;
}
