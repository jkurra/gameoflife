#include "gameobject.h"
#include "../view/view.h"

GameObject *GameObject_new( const char *co, const char *th )
{
    GameObject *rtn = (GameObject*)calloc(1, sizeof(GameObject));

    g_print("creating object\n");
    rtn->conf = config_new(co);
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
    g_print("file menu\n");
    rtn->m_model->builder = gtk_builder_new_from_file("src/view/gui/gof_menu.glade");
    rtn->g_model->builder = gtk_builder_new_from_file("src/view/gui/gof_game_test.glade");
    rtn->p_model->builder = gtk_builder_new_from_file("src/view/gui/gof_pref.glade");
    g_print("file menu\n");
    return rtn;
}

void GameObject_select_view( GameObject *object, int view )
{g_print("file m1enu\n");

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
    switch (view) {
        case MENU:
            //object->m_model->builder = gtk_builder_new_from_file("src/view/gui/gof_menu.glade");
            g_print("file m1enu\n");
            object->selected = MENU;
            view_init((Model*)object->m_model, object);
            break;
        case GAME:

            //gtk_widget_destroy(GTK_WIDGET(object->m_model->main_frame));
            //g_object_unref (G_OBJECT(object->m_model->main_frame));
            //view_close(object->m_model);
            //g_print("Close menu\n");
            //view_close((Model*)object->m_model);
            //g_print("Start game\n");
            object->selected = GAME;
            //object->g_model->builder = gtk_builder_new_from_file("src/view/gui/gof_game_test.glade");
            view_init((Model*)object->g_model, object);
            gtk_main();
            g_print("Done\n");
            break;
        case PREF:
        //    object->p_model->builder = gtk_builder_new_from_file("src/view/gui/gof_pref.glade");
            object->selected = PREF;
            view_init((Model*)object->p_model, object);
            break;
        default:
            break;
    }
}

void GameObject_init( GameObject *object )
{
g_print("file menu\n");
    gsize bytes_written, bytes_read;
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default ();
    GdkScreen  *screen  = gdk_display_get_default_screen (display);
    GError *error = 0;
    g_print("file menu\n");
    //gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    //gchar *fname = g_filename_to_utf8(object->g_model->themes->sel_path, strlen(object->g_model->themes->sel_path), &bytes_read, &bytes_written, &error);
    //gtk_css_provider_load_from_path(provider , fname, NULL);

    //object->m_model->builder = gtk_builder_new_from_file("src/view/gui/gof_menu.glade");
g_print("file m1enu: %d\n", object->m_model->base.type);
object->selected = MENU;
    view_init((Model*)object->m_model, object);
    g_print("file men1u\n");
    gtk_main();
    //g_object_unref(G_OBJECT(model->builder));

    //g_object_unref(G_OBJECT(provider));
    //g_free(fname);

}
