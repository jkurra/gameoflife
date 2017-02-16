#ifndef GAMEAREA_H_INCLUDED
#define GAMEAREA_H_INCLUDED

#include "../../model/model.h"

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

#endif /* GAMEAREA_H_ */
