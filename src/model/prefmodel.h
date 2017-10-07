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

/** @brief
 *
 */
PrefModel *PrefModel_new();

/** @brief
 *
 */
void PrefModel_free( PrefModel *model );

/** @brief
 *
 */
void PrefModel_read( PrefModel *model, const char *file );

/** @brief
 *
 */
void PrefModel_save( PrefModel *model, const char *file );

#endif /* PREFMODEL_H_ */
