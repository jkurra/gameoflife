#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

#include <stdlib.h>

#include "ruleset.h"

/** @brief Structure for Cell object.
 *
 *  Describes structure of cell, which is located in a position in Grid.
 *  Therefore most important values of cell are row & col, which can be used
 *  to quickly check position of cell. It can also contain data about whether
 *  cell has already been checked. 
 */
typedef struct
{
    /** @brief
     *
     */
    int row;

    /** @brief
     *
     */
    int col;

    /** @brief
     *
     */
    int nbrs_count;

    /** @brief
     *
     */
    int state;

    /** @brief
     *
     */
    int checked;

} Cell;

/** @brief Initialize new cell with given rows.
 *
 */
Cell *Cell_new( int row, int col );

/** @brief Deallocate given cell.
 *
 */
void Cell_free( Cell *cell );

/** @brief Checks state of the cell in previous turn.
 *
 * TODO: NOT YET IMPLEMENTED
 * Based on current state of the cell, it is possible to peek previous state of
 * it. This is done using amount of neighbours and set of rules that apply. All
 * rules are applied as "live" rules, meaning that if those rules are not
 * fulfilled, cell is expected to be dead. This function is useful when it is
 * necessary to apply rules "backwards", for example, to see what happened in
 * previous turn. Rules are applied as integer numbers representing amount
 * of neighbours that keep current live state or turn the cell alive. For example set of [2,3]
 * would compare current amount of neighbours first to 2 and then to 3. If
 * current neighbours would match either of those, cell would have been alive
 * in previous turn. Notice that rules of "reproduction" and "survival"
 * are really only ones that matter since everything else is seen as under or
 * overpopulation, or stagnant state.
 *
 * @param cell
 * @param rules
 * @return state of the cell in previous turn.
 */
int Cell_prev( Cell *cell, RuleSet *rules );

/** @brief Checks state of the cell in next turn.
 *
 * Based on current state of the cell, it is possible to peek future state of
 * it. This is done using amount of neighbours and set of rules that apply. All
 * rules are applied as "live" rules, meaning that if those rules are not
 * fulfilled, cell is expected to be dead. This function is useful when it is
 * necessary to peek future value of the cell. Rules are applied as integer
 * values representing amount of neighbours that keep the current alive state or turn the cell alive.
 * For example set of [2,3] would compare current amount of neighbours first
 * to 2 and then to 3. If current neighbours would match either of those, cell
 * would be alive next turn. Notice that rules of "reproduction" and "survival"
 * are really only ones that matter since everything else is seen as under or
 * overpopulation, or stagnant state.
 *
 * @param cell
 * @param rules
 * @return state of the cell in next turn.
 */
int Cell_next( Cell *cell, RuleSet *rules );

#endif /* CELL_H_ */
