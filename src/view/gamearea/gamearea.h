#ifndef GAMEAREA_H_INCLUDED
#define GAMEAREA_H_INCLUDED

#include <gtk/gtk.h>

#include "../../model/model.h"
#include "../../model/viewobject.h"

#include "../../model/prefmodel.h"
#include "../../model/gamemodel.h"
#include "../../model/menumodel.h"

#include "../../engine/board/board.h"

typedef struct {
    GameModel *game;
    GameEngine *engine;
} gamedata;

/*
 *
 */
int GameArea_clicked_y_pos( gpointer data, float y );

/*
 *
 */
int GameArea_clicked_x_pos( gpointer data, float x );

/*
 *
 */
void  GameArea_draw_nodes();

/*
 *
 */
void draw_GameArea( GtkDrawingArea *area, cairo_t *cr, gpointer data );
void draw_MenuArea( GtkDrawingArea *area, cairo_t *cr, gpointer data );
/*
 *
 */
int read_row_index( GtkWidget game_area, float x_point, float y_point );

/*
 *
 */
int read_col_index( GtkWidget game_area, float x_point, float y_point );

/*
 *
 */
int GameArea_y_pos( GameEngine *engine, float y );

/*
 *
 */
int GameArea_x_pos( GameEngine *engine, float x );

#endif /* GAMEAREA_H_ */
