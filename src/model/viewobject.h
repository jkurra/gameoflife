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

/** @brief Object containing view data.
 *
 */
typedef struct
{
    /* Type of currently selected view.  */
    int selected;

    /* Configuration manager */
    Manager *conf;
    /* Theme manager */
    Manager *theme;

    /* Model containing data for menu-view.  */
    MenuModel *m_model;
    /* Model containing data for game-view.  */
    GameModel *g_model;
    /* Model containing data for preferences-view.  */
    PrefModel *p_model;

} ViewObject;

/** @brief Allocate new ViewObject.
 *
 *  Allocates viewobject and Managers and models in it.
 *
 */
ViewObject *ViewObject_new( const char *co, const char *th );

/** @brief Initialize ViewObject.
 *
 *  Initializes needed builders, screens etc. needed to start main loop
 *  and show views.
 */
void ViewObject_init( ViewObject *object );

/** @brief Quit ViewObject and free everything in it.
 *
 */
void ViewObject_quit( ViewObject *object );

/** @brief Select new view to be shown.
 *
 *  Hides currently selected view from user (and stops timer actions) and shows
 *  view newView.
 *
 */
void ViewObject_select( ViewObject *object, int newView );

#endif /* SIGNAL_H_ */
