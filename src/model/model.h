#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <gtk/gtk.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "../manager/manager.h"
#include "../data/grid.h"
#include "../manager/json/json.h"
#include "../manager/json/file.h"

/* Types of views that may be used */
#define MENU  0
#define GAME  1
#define PREF  2

/*
 *
 */
typedef struct
{
	int type;
} Model;

/*
 *
 */
typedef struct
{
	Model base;

	GdkRGBA bgrn_col; /* Background color of the grid */
	GdkRGBA cell_col; /* Color of each cell in grid */

	int rows, cols; /* Maximum dimensions of the game grid */
	int infinite;
	int visible;

	float cell_s;		/* Size of each cell in the screen. */
	float zoom; 		/* How big or small cells appear on the screen.	*/
	float spacing;
	int interval;
	int c_step;
	int timerid;	/* Id of the widget containing update timer. */
	int **grid;
	/* RULES */
	int *live_a, *live_d;
	Manager *themes;
	Manager *conf;
	GtkBuilder *builder;

	GtkWidget *main_frame;
	GtkWidget *game_frame;
} GameModel;

/*
 *
 */
typedef struct
{
	Model base;
	Manager *themes;
	Manager *conf;

	GtkBuilder *builder;
	GtkWidget  *main_frame;
} MenuModel;

/*
 *
 */
typedef struct
{
	Model base;
	Manager *themes;
	Manager *conf;

	GtkBuilder *builder;
	GtkWidget  *main_frame;
} PrefModel;

/*
 *
 */
Model *model_new();

/*
 *
 */
void model_free( Model *model );

GameModel *GameModel_new();

void GameModel_free( GameModel *model );
void GameModel_save( GameModel *model );
void GameModel_read( GameModel *model, const char *file );

PrefModel *PrefModel_new();

void PrefModel_free( PrefModel *model );

void PrefModel_read( PrefModel *model, const char *file );

MenuModel *MenuModel_new();

void MenuModel_free( MenuModel *model );

void MenuModel_read( MenuModel *model, const char *file );

#endif /* MODEL_H_ */
