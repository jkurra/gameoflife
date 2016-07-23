#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

#define X_SIZE 0
#define Y_SIZE 0

/** @brief Checks state of the cell in previous turn.
 *
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
 * @param c_state current state of the cell. Alive = 1, Dead = 0
 * @param nbrs    Current amount of neighbours for the cell (between 0-8).
 * @param live_a  Set of rules that apply if cell is currently dead.
 * @param live_d  Set of rules that aplly if cell is currently alive.
 * @return state of the cell in previous turn.
 */
int cell_prev( int c_state, int nbrs, int *live_a, int *live_d );

/** @brief Checks state of the cell in next turn.
 * NOT YET IMPLEMENTED
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
 * @param c_state current state of the cell. Alive = 1, Dead = 0
 * @param nbrs    Current amount of neighbours for the cell (between 0-8).
 * @param live_a  Set of rules that apply if cell is currently dead.
 * @param live_d  Set of rules that aplly if cell is currently alive.
 * @return state of the cell in next turn.
 */
int cell_next( int c_state, int nbrs, int live_a[], int live_s, int live_d[], int dead_s ) ;

#endif /* CELL_H_ */
