#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include "../manager/theme.h"
#include "../manager/config.h"

#include <gtk/gtk.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <string.h>

/* Types of views that may be used */
#define MENU  0
#define GAME  1
#define PREF  2

/* @brief A model containing application wide universal values.
 *
 *  Makes using single model for values that may need to be set in different
 *  views possible. This should simplify error handling and prevent data loss.
 *
 */
typedef struct
{
	GdkRGBA bgrn_col; /* Background color of the grid */
	GdkRGBA cell_col; /* Color of each cell in grid */

	int rows, cols; /* Maximum dimensions of the game grid */
	int infinite;
	int visible;

	float cell_s;		/* Size of each cell in the screen. */
	float zoom; 		/* How big or small cells appear on the screen.	*/
	int interval;

	int timerid;	/* Id of the widget containing update timer. */

	/* RULES */
	int *live_a;
	int *live_d;

	//char *theme_path;
	char *config_path;
	config *conf;
	theme *themes;
} commons_model;

/*
 *
 */
typedef struct
{
	GtkWidget *main_frame;
	commons_model *commons; /* Common values for this model. May be NULL */

} menu_model;

/*
 *
 */
typedef struct
{
	GtkWidget *main_frame;
	commons_model *commons; /* Common values for this model. May be NULL */

} pref_model;

/*
 *
 */
typedef struct
{
	GtkWidget *main_frame; /* Main widget containing elements of the view */
	GtkWidget *game_area;
	commons_model *commons; /* Common values for this model. May be NULL */

	int  c_rows, c_cols; /* Current row/column count */
	int **grid;			/* Game board containing values */
	int c_step;

	int startAtCellX; /* From which column to start drawing */
	int startAtCellY; /* From which row to start drawing */

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

	commons_model *commons;

	GtkBuilder *builder;
	GtkCssProvider *provider;

} view_model;
/** @brief Initialize values current model.
 *
 * Initializes view using view_model, which contains type value. Type value is
 * used to determine which model is to be initialized. Therefore it must be set
 * before calling this function, otherwise behaviour may be unexpected. It is
 * also good to notice that this function doesn't free views that may be
 * initialized, so that must be taken care of before calling this function to
 * avoid double assingments of widgets. This function is meant to be used when
 * it is necessary to initialize view using view_model. This way all necessary
 * data is present when values are assigned.
 *
 * @param model Contains data needed to initialize view.
 */
void view_init( view_model *model, int type );


/** @brief Draw current model.
 *
 * Adds selected view to gtk-widget draw queue. Gives quick way of updating the
 * view without having to select which view needs to be drawn. As long as
 * view_model contains correct view and type, it can automatically select right
 * update function.
 *
 * @param model Contains view to be updated.
 */
void view_draw(view_model *model);

/** @brief Close current model.
 *
 * unrefs and calls destroy on currently active views main widget. Notice that
 * type must point to correct widget type or it may try to release incorrect
 * view. Make sure to call this before changing widget type and calling init_view.
 * Purpose of this function is to provide quick way of freeing view. However since
 * view_model contains multiple sub-views it is up to user to make sure that
 * correct view is selected. In future more checks may be assigned to avoid
 * mistakes.
 *
 * @param model Contains view to be closed.
 */
void view_close( view_model *model );

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
