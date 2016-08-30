#ifndef GAMEAREA_H_INCLUDED
#define GAMEAREA_H_INCLUDED

#include <gtk/gtk.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/gl.h>

int GameArea_x_pos( gpointer data, float x, float width, float height );

int GameArea_y_pos( gpointer data, float y, float width, float height );

void GameArea_draw_rectanle(  cairo_t *cairo, GdkRGBA *color, int start_x, int start_y, int width, int height );

#endif /* GAMEAREA_H_ */
