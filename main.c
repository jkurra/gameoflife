#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/gl.h>

#include "src/manager/theme.h"
#include "src/manager/config.h"
#include "src/output/log.h"
#include "src/model/model.h"
#include "src/view/view.h"

Model *GameObject_select( int type )
{
    Model *mrtn = NULL;

    switch (type) {
        case MENU: {
            MenuModel *m1 = MenuModel_new();
            mrtn = (Model*)m1;
            break;
        }
        case GAME: {
            GameModel *m2 = GameModel_new();
            mrtn = (Model*)m2;
            break;
        }
        case PREF: {
            PrefModel *m3 = PrefModel_new();
            mrtn = (Model*)m3;
            break;
        }
        default:
            break;
    }

    return mrtn;
}

void GameObject_init( const char *co, const char *th)
{
    Manager *conf = config_new(co);
    Manager *theme = theme_new(th);
    config_select(conf, "config.json");
    theme_select(theme, "default");

    /* Create new main model for our game */
    GameModel *model = (GameModel*)GameObject_select(GAME);//GameModel_new();
    /* Read values from file. */
    GameModel_read(model, conf->sel_path);
    model->themes = theme;
    model->conf = conf;
    g_print("rows:%d\n", model->rows);
    gtk_init(NULL, NULL);
    gsize bytes_written, bytes_read;
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default ();
    GdkScreen  *screen  = gdk_display_get_default_screen (display);
    GError *error = 0;
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gchar *fname = g_filename_to_utf8(theme->sel_path, strlen(theme->sel_path), &bytes_read, &bytes_written, &error);
    gtk_css_provider_load_from_path(provider , fname, NULL);
    //GtkBuilder *builder = gtk_builder_new_from_file("src/view/gui/gof_game_test.glade");
    //g_object_unref(G_OBJECT(builder));
    model->builder = gtk_builder_new_from_file("src/view/gui/gof_game_test.glade");
    view_init((Model*)model);
    gtk_main();
    g_object_unref(G_OBJECT(model->builder));
//    gtk_main();

    g_object_unref(G_OBJECT(provider));

    g_free(fname);
    GameModel_free(model);

    config_free(conf);
    theme_free(theme);
}
int main(int argc, char *argv[])
{
    /*
        Find out current filepath so we can use confing file.
        TODO: file should be allocated and freed with dedicated functions.
              Now it is freed in model.
     */
     char cwd[1024];
     if(getcwd(cwd, sizeof(cwd)) != 0) {
         printf("[%s] Startup - dir : %s\n",log_timestamp(), cwd);
         //fprintf(stdout, "Current working dir: %s\n", cwd);
     } else { perror("getcwd() error"); }
    char fname[15]  = "/config/config"; /* Add place for default config file */
    size_t lenght = strlen(cwd) + strlen(fname)+1;

    char *result = (char*)malloc(sizeof(char)*lenght);
    char *co = (char*)malloc(sizeof(char)*lenght+28);
    char *th = (char*)malloc(sizeof(char)*lenght+19);

    strcpy( result, cwd );
    strcat( result, fname );
    /* prepare config file selection, for testing */
    strcpy( co, cwd );
    strcat( co, "/usr/config" );

    strcpy( th, cwd );
    strcat( th, "/usr/themes" );

    GameObject_init(co, th);

    free(co);
    free(th);
    free(result);

    return 0;
}
