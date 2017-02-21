#include "viewobject.h"
#include "../view/view.h"

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

    rtn->g_model->conf =rtn->conf;
    rtn->g_model->themes =rtn->theme;

    rtn->p_model->conf =rtn->conf;
    rtn->p_model->themes =rtn->theme;

    MenuModel_read(rtn->m_model, rtn->conf->sel_path);
    GameModel_read(rtn->g_model, rtn->conf->sel_path);
    PrefModel_read(rtn->p_model, rtn->conf->sel_path);

    rtn->m_model->builder = gtk_builder_new_from_file("src/view/gui/gof_menu.glade");
    rtn->g_model->builder = gtk_builder_new_from_file("src/view/gui/gof_game_test.glade");
    rtn->p_model->builder = gtk_builder_new_from_file("src/view/gui/gof_pref.glade");

    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen  *screen  = gdk_display_get_default_screen(display);

    return rtn;
}

void ViewObject_close_selected( ViewObject *object )
{
    if(object) {
        switch (object->selected) {
            case MENU:
                view_close((Model*)object->m_model);
                break;
            case GAME:
                view_close((Model*)object->g_model);
                break;
            case PREF:
                view_close((Model*)object->p_model);
                break;
            default:
                break;
        }
    }
}

void ViewObject_select( ViewObject *object, int view )
{
    if(object) {
        /* Close any currently visible view in program. */
        ViewObject_close_selected(object);

        switch (view) {
            case MENU:
                object->selected = MENU;
                view_init((Model*)object->m_model, object);
                break;
            case GAME:
                object->selected = GAME;
                view_init((Model*)object->g_model, object);
                break;
            case PREF:
                object->selected = PREF;
                view_init((Model*)object->p_model, object);
                break;
            default:
                break;
        }
        /*
            Start main loop.
            TODO: check if main loop must be started each time window is deleted.
        */
        gtk_main();
    }
}
