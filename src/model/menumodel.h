#ifndef MENUMODEL_H_INCLUDED
#define MENUMODEL_H_INCLUDED

#include "model.h"

/** @brief
 *
 */
typedef struct
{
	/** @brief
	 *
	 */
	Model base;

	/** @brief
	 *
	 */
	Manager *themes;

	/** @brief
	 *
	 */
	Manager *conf;

	GtkBuilder *builder;
	GtkWidget *main_frame;
	GtkWidget *game_frame;

	Grid *grid;

} MenuModel;

/** @brief
 *
 */
MenuModel *MenuModel_new();

/** @brief
 *
 */
void MenuModel_free( MenuModel *model );

/** @brief
 *
 */
void MenuModel_read( MenuModel *model, const char *file );

/** @brief
 *
 */
 void MenuModel_save( MenuModel *model, const char *file );

#endif /* MENUMODEL_H_ */
