#ifndef GAMEMODEL_H_INCLUDED
#define GAMEMODEL_H_INCLUDED

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

	int is_playing;
	/** @brief
	 *
     */
	GdkRGBA bgrn_col; /* Background color of the grid */

	/** @brief
	 *
     */
	GdkRGBA cell_col; /* Color of each cell in grid */

	/** @brief
	 *
     */
	int infinite;

	/** @brief
	 *
     */
	int visible;
	int updated;

	float cell_s;		/* Size of each cell in the screen. */
	float zoom; 		/* How big or small cells appear on the screen.	*/
	float spacing;
	int interval;
	int c_step;
	int timerid;	/* Id of the widget containing update timer. */
	int startX;
	int startY;

	Grid *grid;
	/* RULES */
	RuleSet *ruleset;
	//int *live_a, *live_d;
	Manager *themes;
	Manager *conf;
	GtkBuilder *builder;

	GtkWidget *main_frame;
	GtkWidget *game_frame;

	time_t *timer;

} GameModel;

/** @brief
 *
 */
GameModel *GameModel_new();

/** @brief
 *
 */
void GameModel_free( GameModel *model );

/** @brief
 *
 */
void GameModel_read( GameModel *model, const char *file );

/** @brief
 *
 */
void GameModel_save( GameModel *model );

#endif /* MODEL_H_ */
