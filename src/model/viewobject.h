#ifndef VIEWOBJECT_H_INCLUDED
#define VIEWOBJECT_H_INCLUDED

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/gl.h>

#include "../manager/theme.h"
#include "../manager/config.h"
#include "../output/log.h"
#include "../model/model.h"

/*
 *
 */
typedef struct
{
    int selected;

    Manager *conf;
    Manager *theme;

    MenuModel *m_model;
    GameModel *g_model;
    PrefModel *p_model;
} ViewObject;

void ViewObject_select( ViewObject *object, int newView );

ViewObject *ViewObject_new( const char *co, const char *th );



#endif /* SIGNAL_H_ */
