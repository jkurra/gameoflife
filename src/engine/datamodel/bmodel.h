#ifndef BMODEL_H_INCLUDED
#define BMODEL_H_INCLUDED

/** @brief
 *
 */
typedef struct
{
	/** @brief
	 *
	 */
	char *bgrn_col;

	/** @brief
	 *
	 */
	float cell_s;		/* Size of each cell in the screen. */

	/** @brief
	 *
	 */
	float space;

	/** @brief
	 *
	 */
	float margin_left;

	/** @brief
	 *
	 */
	float margin_right;

	/** @brief
	 *
	 */
	float margin_up;

	/** @brief
	 *
	 */
	float margin_down;

	/** @brief
	 *
	 */
	float zoom; 		/* User defined modifier for size of the cells	*/

} BModel;

/** @brief
 *
 */
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

char *BModel_json( BModel *bmodel );

#endif /* MODEL_H_ */
