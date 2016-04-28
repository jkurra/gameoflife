#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "model.h"

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
    char *result = malloc(lenght);

    strcpy( result, cwd );
    strcat( result, fname );
    /* Create new main model for our user interface */
    view_model *main_model = model_view_new(MENU, result);
    /* Initialize view free when user quit */
    model_init_view(main_model, MENU); /* Init menu and start main GTK loop */
    model_view_free(main_model); /* User quit. */

    return 0;
}
