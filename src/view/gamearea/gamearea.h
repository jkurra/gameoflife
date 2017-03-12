#ifndef GAMEAREA_H_INCLUDED
#define GAMEAREA_H_INCLUDED

#include "../../model/model.h"
#include "../../model/viewobject.h"

#include <gtk/gtk.h>

/*
 *
 */
void draw_GameArea( GtkDrawingArea *area, cairo_t *cr, gpointer data);

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
int GameArea_y_pos( gpointer data, float y, float width, float height );

/*
 *
 */
int GameArea_x_pos( gpointer data, float x, float width, float height );

#endif /* GAMEAREA_H_ */
