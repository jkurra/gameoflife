#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include "view.h"
#include "jsmn/jsm.h"

#define MENU  0
#define GAME  1
#define PREF  2

gboolean model_grid_update( view_model *game_data );

/*
 *
 */
void model_init_view( view_model *model );

/*
 *
 */
void model_draw_view( view_model *model );



#endif
