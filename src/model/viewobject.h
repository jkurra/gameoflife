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
    /** @brief
	 *
     */
    int selected;

    /** @brief
	 *
     */
    Manager *conf;

    /** @brief
	 *
     */
    Manager *theme;

    /** @brief
	 *
     */
    MenuModel *m_model;

    /** @brief
	 *
     */
    GameModel *g_model;

    /** @brief
	 *
     */
    PrefModel *p_model;

    pthread_t gameThread;

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

void ViewObject_start_grid_loop( ViewObject *object );

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
