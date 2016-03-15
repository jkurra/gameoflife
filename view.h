#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include "grid.h"

#include <gtk/gtk.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/gl.h>

/*
 *
 */
typedef struct
{
	GtkWidget *main_frame;
} menu_model;

/*
 *
 */
typedef struct
{
	GtkWidget *main_frame;
} pref_model;

/*
 *
 */
typedef struct
{
	GtkWidget *main_frame; /* Main widget containing elements of the view */

	GdkRGBA bgrn_col; /* Background color of the grid */
	GdkRGBA cell_col; /* Color of each cell in grid */

	int max_x, max_y; /* Maximum dimensions of the game grid */
	int **grid;				/* Game board containing values */
	int infinite;
	int visible;

  /* TODO: remove */



  /* TODO: end remove */

	float cell_s;		/* Size of each cell in the screen. */
	float zoom; 		/* How big or small cells appear on the screen.	*/
	int tick_t;

	int timerid;	/* Id of the widget containing update timer. */

	int startAtCellX; /* From which column to start drawing */
	int startAtCellY; /* From which row to start drawing */

	/* RULES */
	int *live_a;
	int *live_d;

} game_model;

/*
 *
 */
typedef struct
{
	int type;

	menu_model *menu;
	game_model *game;
	pref_model *pref;

	char **pref_path;
} view_model;


gboolean model_grid_update( view_model *game_data );

/** @brief Initialize menu view.
 *
 */
void view_menu_init( view_model *model );

/** @brief Initialize game view.
 *
 */
void view_game_init( view_model *model );

/** @brief Initialize pref view.
 *
 */
void view_pref_init( view_model *model );

#endif
