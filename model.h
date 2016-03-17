#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include "view.h"
#include "jsmn/jsm.h"
#include <stdlib.h>
#define MENU  0
#define GAME  1
#define PREF  2

/** @brief Initialize current model.
 *
 */
void model_init_view( view_model *model );

/** @brief Draw current model.
 *
 */
void model_draw_view( view_model *model );

/** @brief Close current model.
 *
 */
void model_close_view( view_model *model );

void model_update( view_model *model, int type );

void model_rwrite( view_model *model, int type );

#endif
