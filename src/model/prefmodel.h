#ifndef PREFMODEL_H_INCLUDED
#define PREFMODEL_H_INCLUDED

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
	GtkWidget  *main_frame;

} PrefModel;


PrefModel *PrefModel_new();
void PrefModel_free( PrefModel *model );
void PrefModel_read( PrefModel *model, const char *file );

#endif /* PREFMODEL_H_ */
