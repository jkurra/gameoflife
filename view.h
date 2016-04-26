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

	GdkRGBA bgrn_col; /* Background color of the grid */
	GdkRGBA cell_col; /* Color of each cell in grid */

	int max_rows, max_y; /* Maximum dimensions of the game grid */
	//int **grid;				/* Game board containing values */
	int infinite;
	int visible;

	float cell_s;		/* Size of each cell in the screen. */
	float zoom; 		/* How big or small cells appear on the screen.	*/
	int tick_t;

	int timerid;
} pref_model;

/*
 *
 */
typedef struct
{
	GtkWidget *main_frame; /* Main widget containing elements of the view */
	GtkWidget *game_area;

	GdkRGBA bgrn_col; /* Background color of the grid */
	GdkRGBA cell_col; /* Color of each cell in grid */

	int max_rows, max_y; /* Maximum dimensions of the game grid */
	int **grid;			/* Game board containing values */
	int infinite;
	int visible;

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
	GtkBuilder *builder;
} view_model;


/** @brief Initialize menu view.
 *
 */
void view_menu_init( menu_model *model, GtkBuilder *builder );

/** @brief Initialize game view.
 *
 */
void view_game_init( game_model *model, GtkBuilder *builder );

/** @brief Initialize pref view.
 *
 */
void view_pref_init( pref_model *model, GtkBuilder *builder );

/** @brief Close menu view.
 *
 * Closes all UI-related items (Widgets etc.) and makes sure that
 * @param model
 */
void view_menu_close( menu_model *model );

/** @brief Close game view.
 *
 */
void view_game_close( game_model *model );

/** @brief Close pref view.
 *
 */
void view_pref_close( pref_model *model );

GtkAllocation *view_widget_pos( GtkWidget *widget );

gboolean view_timer_update( game_model *model );

#endif /* VIEW_H_ */
