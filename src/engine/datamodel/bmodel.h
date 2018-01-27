#ifndef BMODEL_H_INCLUDED
#define BMODEL_H_INCLUDED
#include <gtk/gtk.h>
#include "stdlib.h"

/** @brief
 *
 */
typedef struct
{
	GdkRGBA bgrn_col;

	float cell_s;		/* Size of each cell in the screen. */
	float space;

	float margin_left;
	float margin_right;
	float margin_up;
	float margin_down;

	float zoom; 		/* User defined modifier for size of the cells	*/


} BModel;

BModel *BModel_new();

void BModel_margin( float left, float right, float up, float down );

void BModel_spacing();
void BModel_bg_color();

void BModel_set_size();
void BModel_set_zoom();

/** @brief
 *
 */
void BModel_save( BModel *model );

/** @brief
 *
 */
void BModel_read( BModel *model );

#endif /* MODEL_H_ */
