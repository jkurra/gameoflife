#include "view.h"

int main(int argc, char *argv[])
{
  char cwd[1024];

  if (getcwd(cwd, sizeof(cwd)) != NULL)
      fprintf(stdout, "Current working dir: %s\n", cwd);
  else {
    perror("getcwd() error");
  }

  char *fname  = "/config/config";
  char *result = malloc( strlen(cwd) + strlen(fname)+1 );  //+1 for the zero-terminator

  strcpy( result, cwd );
  strcat( result, fname );

	menu_model menu;
	game_model game;
	pref_model pref;

	view_model main_model;

  main_model.type = 0; /* initialize menu */

	main_model.menu = &menu;
	main_model.game = &game;
	main_model.pref = &pref;

  /*
    gdk_rgba_parse (&main_model.game->cellColor, "yellow");;
    gdk_rgba_parse (&main_model.game->backGround , "black");;
  */

	main_model.pref_path = result;

  jsm_read_model ( &main_model );
	model_init_view( &main_model );

  free(result);

  return 0;
}
