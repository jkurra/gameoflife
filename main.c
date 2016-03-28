#include "view.h"
#include "model.h"

int main(int argc, char *argv[])
{
  char cwd[1024];

  if ( getcwd(cwd, sizeof(cwd)) != NULL )
    fprintf(stdout, "Current working dir: %s\n", cwd);
  else {
    perror("getcwd() error");
  }

  char *fname  = "/config/config";
  char *result = malloc( strlen(cwd) + strlen(fname) + 1 );  //+1 for the zero-terminator

  strcpy( result, cwd );
  strcat( result, fname );

  menu_model menu;
  game_model game;
  pref_model pref;

  /*TODO: tmp values, read from confiog file */
  int live_a1[2] = { 3, 2 };
  int live_d1[1] = { 3 };

  /* set default values for game */
  game.timerid = -1;
  game.live_a  = &live_a1;
  game.live_d  = &live_d1;

  game.bgrn_col;
  game.cell_col;
  game.max_x = 0;
  game.max_y = 0;
  game.grid = NULL;
  game.infinite =0;
  game.visible = 0;
  game.cell_s = 0;		/* Size of each cell in the screen. */
  game.zoom = 0; 		/* How big or small cells appear on the screen.	*/
  game.tick_t  =0;
  game.timerid = 0;	/* Id of the widget containing update timer. */
  game.startAtCellX = 0; /* From which column to start drawing */
  game.startAtCellY = 0; /* From which row to start drawing */


  view_model main_model;

  main_model.type = 0; /* initialize menu */

  main_model.menu = &menu;
  main_model.game = &game;
  main_model.pref = &pref;

  main_model.pref_path = result;

  //jsm_read_model ( &main_model );
  view_init(&main_model);
  model_update(&main_model, GAME);
  model_init_view ( &main_model );
  view_free(&main_model);

  if( game.grid ) {
      grid_free(game.max_y, game.grid);
  }

  //g_object_ref_sink(G_OBJECT(menu.main_frame));
  //gtk_widget_destroy (menu.main_frame);
//  g_object_unref (G_OBJECT(menu.main_frame));

  free ( result );

  return 0;
}
