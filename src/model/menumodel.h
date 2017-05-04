#ifndef MENUMODEL_H_INCLUDED
#define MENUMODEL_H_INCLUDED

#include "model.h"

/** @brief
 *
 */
typedef struct
{
	Model base;
	Manager *themes;
	Manager *conf;

	GtkBuilder *builder;
	GtkWidget *main_frame;
	GtkWidget *game_frame;

} MenuModel;

MenuModel *MenuModel_new();
void MenuModel_free( MenuModel *model );
void MenuModel_read( MenuModel *model, const char *file );

#endif /* MENUMODEL_H_ */
