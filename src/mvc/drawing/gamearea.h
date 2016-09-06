#ifndef GAMEAREA_H_INCLUDED
#define GAMEAREA_H_INCLUDED

#include <gtk/gtk.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/gl.h>

int GameArea_x_pos( gpointer data, float x, float width, float height );

int GameArea_y_pos( gpointer data, float y, float width, float height );


#endif /* GAMEAREA_H_ */
