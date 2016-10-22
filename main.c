#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "src/manager/theme.h"
#include "src/manager/config.h"
#include "src/manager/log.h"
#include "src/mvc/model.h"

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

    Manager *conf = config_new(co);
    config_select(conf, "config.json");

    /* Create new main model for our user interface */
    view_model *main_model = model_view_new(MENU, conf);

    main_model->game->commons->themes = theme_new(th);
    theme_select(main_model->game->commons->themes, "default");
    model_read(main_model->commons, NULL);
    //theme_select(main_model->game->commons->themes, "default");
    /* Initialize view free when user quit */
    view_init(main_model, MENU); /* Init menu and start main GTK loop */
    model_view_free(main_model); /* User quit. */
    config_free(conf);
    //theme_free(th);
    free(co);
    free(th);
    free(result);

    return 0;
}
