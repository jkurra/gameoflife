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

#include "src/model/viewobject.h"

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

    ViewObject *object = ViewObject_new(co, th);
    ViewObject_init(object);
    ViewObject_select(object, MENU);
    gtk_main();
    ViewObject_quit( object );
    free(co);
    free(th);
    free(result);

    return 0;
}
