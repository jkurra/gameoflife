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
	GtkWidget *main_frame;
	int initilized; /* tells if settings have already been found */
	int grid_x;
	int grid_y;

	int cell_s;
	int tick_t;
	int **grid;

	int timerid;
	int zoom;

	int startAtCellX;
	int startAtCellY;
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

/*
 *
 */
void view_menu_init( view_model *model );

/*
 *
 */
void view_game_init( view_model *model );

/*
 *
 */
void view_pref_init( view_model *model );

#endif
