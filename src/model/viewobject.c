#include "viewobject.h"
#include "../view/view.h"

void ViewObject_connect_signals( ViewObject *object );
void ViewObject_close_selected( ViewObject *object );

ViewObject *ViewObject_new( const char *co, const char *th )
{
    ViewObject *rtn = (ViewObject*)calloc(1, sizeof(ViewObject));
    rtn->selected = -1;
    rtn->conf  = config_new(co);
    rtn->theme = theme_new(th);

    config_select(rtn->conf, "config.json");
    theme_select(rtn->theme, "default");

    gtk_init(NULL, NULL);

    rtn->m_model = MenuModel_new();
    rtn->g_model = GameModel_new();
    rtn->p_model = PrefModel_new();

    rtn->m_model->conf = rtn->conf;
    rtn->m_model->themes = rtn->theme;

    rtn->g_model->conf = rtn->conf;
    rtn->g_model->themes = rtn->theme;

    rtn->p_model->conf = rtn->conf;
    rtn->p_model->themes = rtn->theme;

    if(rtn->conf->sel_path) {
        MenuModel_read(rtn->m_model, rtn->conf->sel_path);
        GameModel_read(rtn->g_model, rtn->conf->sel_path);
        PrefModel_read(rtn->p_model, rtn->conf->sel_path);
    }

    rtn->m_model->builder = gtk_builder_new_from_file("src/view/gui/gof_menu.glade");
    rtn->g_model->builder = gtk_builder_new_from_file("src/view/gui/gof_game.glade");
    rtn->p_model->builder = gtk_builder_new_from_file("src/view/gui/gof_pref.glade");

    return rtn;
}

void ViewObject_init( ViewObject *object )
{
    GtkCssProvider *provider = gtk_css_provider_new();
    GError *error = NULL;
    gtk_css_provider_load_from_path (provider, object->theme->sel_path,  &error);

    GdkDisplay *display = gdk_display_get_default();
    GdkScreen  *screen  = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

void ViewObject_select( ViewObject *object, int view )
{
    if(object) {
        /* Close any currently visible view in program. */
        ViewObject_close_selected(object);

        switch (view) {
            case MENU:
                object->selected = MENU;
                view_show((Model*)object->m_model);
                break;
            case GAME: {
                object->selected = GAME;

                printf("Allocation of the engine \n");
                object->engine = (GameEngine*)calloc(1, sizeof(GameEngine));
                // object->g_model->engine = object->engine;
                GameView_show( object->g_model, object->engine );
                //view_show((Model*)object->g_model);
                //engine->node_count = 0;
                object->engine->RUNNING = 1;
                object->engine->interval = 10000;
                object->engine->board = Board_new(30, 30);//Grid_new(object->g_model->grid->gArray->rows,object->g_model->grid->gArray->cols);
                object->engine->bmodel = BModel_new();
                //object->engine->area->gmodel = object->g_model;
                object->engine->gmodel = object->g_model;
                GameEngine_mainloop(object->engine);
                break;
            }
            case PREF:
                object->selected = PREF;
                view_show((Model*)object->p_model);
                break;
            default:
                break;
        }
        /*
         *  Connect signals using builder in the Models and object as an
         *  additional parameter.
         */
        ViewObject_connect_signals(object);
    }
}

void *gameLoopThread(void *arg)
{
    ViewObject *object = (ViewObject*)arg;

    while(object->g_model->is_playing) {
        Grid_next(object->g_model->grid, object->g_model->ruleset);

        for(int i=0; i<object->g_model->grid->lArray->base.count; i++) {
            printf("array: %d\n",object->g_model->grid->lArray->base.count );
            Board_add( object->engine->board, Node_new(CellArray_get( object->g_model->grid->lArray, i )->row, CellArray_get( object->g_model->grid->lArray, i )->col));
        //    CellArray_get( object->g_model->grid->lArray, i )->row;
        //    CellArray_get( object->g_model->grid->lArray, i )->col;

        }
        //GameArea1_add_node( GameArea1 *area, Node *node ;
        //grid_next(model->rows, model->cols, model->grid, model->live_a, 2, model->live_d, 1);
        object->g_model->c_step++;
        //object->g_model->interval;
        //object->g_model->updated = 1;
        usleep(object->g_model->interval*1000);
    }
    return NULL;
}

void ViewObject_start_grid_loop( ViewObject *object )
{
    //pthread_t *gameThread;
    object->g_model->is_playing = 1;
    pthread_create(&object->gameThread, NULL, gameLoopThread, object);
    //pthread_join(thread, NULL);
}

void ViewObject_quit( ViewObject *object )
{
    g_print("calling viewvobject quit...\n");
    if(object) {
        if(object->g_model->is_playing) {
            object->g_model->is_playing = 0;
        }

        pthread_join(object->gameThread, NULL);

        if(object->g_model){
            view_destroy((Model*)object->g_model);
        }
        if(object->p_model) {
            view_destroy((Model*)object->p_model);
        }
        if(object->m_model){
            view_destroy((Model*)object->m_model);
        }
        /*
        theme_free(object->theme );
        config_free(object->conf );
        */
        //g_object_unref(object->m_model->builder);
        //g_object_unref(object->g_model->builder);
        //g_object_unref(object->p_model->builder);
        MenuModel_free(object->m_model);
        GameModel_free(object->g_model);
        PrefModel_free(object->p_model);

        free(object);
        object = NULL;

    }
}

void ViewObject_close_selected( ViewObject *object )
{
    if(object) {
        switch (object->selected) {
            case MENU:
                view_hide((Model*)object->m_model);
                break;
            case GAME:
                view_hide((Model*)object->g_model);
                break;
            case PREF:
                view_hide((Model*)object->p_model);
                break;
            default:
                break;
        }
    }
}

void ViewObject_connect_signals( ViewObject *object )
{
    if(object) {
        /*
            Auto-connect signals in glade files to defined signals.
            Signals can be located in src/view/signal/signal.h file.
        */
        switch (object->selected) {
            case MENU:
                gtk_builder_connect_signals(object->m_model->builder, object);
                g_signal_connect( G_OBJECT( object->m_model->game_frame ), "draw", G_CALLBACK(draw_MenuArea), object->m_model );
                break;
            case GAME:
                gtk_builder_connect_signals(object->g_model->builder, object);
                g_signal_connect( G_OBJECT( object->g_model->game_frame ), "draw", G_CALLBACK(draw_GameArea), object->engine);
                break;
            case PREF:
                gtk_builder_connect_signals(object->p_model->builder, object);
                break;
            default:
                break;
        }
    }
}
