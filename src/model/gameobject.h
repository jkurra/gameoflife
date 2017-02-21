#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/gl.h>

#include "../manager/theme.h"
#include "../manager/config.h"
#include "../output/log.h"
#include "../model/model.h"

typedef struct
{
    int selected;
    Manager *conf;
    Manager *theme;

    MenuModel *m_model;
    GameModel *g_model;
    PrefModel *p_model;
} GameObject;

GameObject *GameObject_new( const char *co, const char *th );

void GameObject_select_view( GameObject *object, int view );
void GameObject_init( GameObject *object );

#endif /* SIGNAL_H_ */
