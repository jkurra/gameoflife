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

/*void GameEngine_add_node( GameEngine *engine, Node *node )
{
    //array->c_array = (Cell**)realloc(array->c_array, (array->base.count+1)*sizeof(Cell*));
    engine->nodes = (Node**)realloc(engine->nodes, (engine->node_count+1)*sizeof(Node*));
    engine->nodes[engine->node_count+1] = node;
    engine->node_count++;
}*/
/*
void GameEngine_remove_node(GameEngine *engine, int index)
{

}*/

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
