#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "manager/theme.h"
#include "manager/config.h"
#include "mvc/model.h"

int main(int argc, char *argv[])
{
    /*
        Find out current filepath so we can use confing file.
        TODO: file should be allocated and freed with dedicated functions.
              Now it is freed in model.
     */
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) != 0) {
        fprintf(stdout, "Current working dir: %s\n", cwd);
    } else { perror("getcwd() error"); }
    char fname[15]  = "/config/config"; /* Add place for default config file */
    size_t lenght = strlen(cwd)+strlen(fname)+1;
    char *result = (char*)malloc(sizeof(char)*lenght);
    char *co = (char*)malloc(sizeof(char)*lenght+8);
    char *th = (char*)malloc(sizeof(char)*lenght+19);

    strcpy( result, cwd );
    strcat( result, fname );
    /* prepare config file selection, for testing */
    strcpy( co, cwd );
    strcat( co, "/config" );

    strcpy( th, cwd );
    strcat( th, "/glade-ui/default/" );

    config *conf = config_new(co);
    config_select(conf, "config.json");

    theme *thm = theme_new(th);
    theme_select(thm, "default.css");
    /* Create new main model for our user interface */
    view_model *main_model = model_view_new(MENU, conf->path_sel);//config_path(conf));
    /* Initialize view free when user quit */
    view_init(main_model, MENU); /* Init menu and start main GTK loop */
    model_view_free(main_model); /* User quit. */
    config_free(conf);

    return 0;
}
