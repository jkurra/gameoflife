#include "view.h"
#include "model.h"

int main(int argc, char *argv[])
{
   /* Find out current filepath so we can use confing file. */
  char cwd[1024];
  if ( getcwd(cwd, sizeof(cwd)) != NULL )
    fprintf(stdout, "Current working dir: %s\n", cwd);
  else {
    perror("getcwd() error");
  }
  char *fname  = "/config/config"; /* Add place for default config file */
  char *result = malloc( strlen(cwd) + strlen(fname) + 1 );

  strcpy( result, cwd );
  strcat( result, fname );
  /* Create new main model for our user interface */
  view_model *main_model = model_view_new(MENU, result);
  /* Update models with values from json file */
  model_update(main_model, GAME);
  model_update(main_model, PREF);
  /* Initialize view free when user quit */
  model_init_view(main_model); /* Init menu and start main GTK loop */
  model_view_free(main_model);

  return 0;
}
