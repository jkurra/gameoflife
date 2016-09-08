#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <gtk/gtk.h>

#include "../data/grid.h"
#include "../manager/config.h"
#include "../manager/theme.h"

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
	float spacing;
	int interval;

	int timerid;	/* Id of the widget containing update timer. */

	/* RULES */
	int *live_a;
	int *live_d;

	Manager *conf;
	Manager *themes;
} commons_model;

/*
 *
 */
typedef struct
{
	GtkWidget *main_frame;
	GtkWidget *game_area;

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

/* @brief Initializes new view_model
 *
 * Initializes view model containing game, menu and pref-models. This way any
 * function of those models may be accessed through view_model. It also creates
 * simple and fast way of initializing all necessary models safely without having
 * to initalize every model individually. It is then possible to change active
 * model to close and open other views included in this model. Must be freed
 * using model_view_free.
 *
 * @param type Type of the model that is set active.
 * @param pref_path Path to file containing settings.
 * @return Pointer to newly allocated view_model.
 */
view_model *model_view_new( int type, Manager *conf );

/* @brief Update
 *
 */
void model_update( view_model *model, int type );

/* @brief Free given model.
 *
 */
void model_view_free( view_model *model );

/* @brief Attach update function id to timer
 *
 */
void model_attach_timer( view_model *model, int interval );

/* @brief Remove timer
 *
 */
void model_remove_timer( view_model *model, int timer_id );

#endif /* MODEL_H_ */
