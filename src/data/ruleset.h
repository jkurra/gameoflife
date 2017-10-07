#ifndef RULESET_H_INCLUDED
#define RULESET_H_INCLUDED

/** @brief Structure for GameGrid object.
 *
 */
typedef struct
{
    /** @brief
     *
     */
    int *live_a;

    /** @brief
     *
     */
    int live_s;

    /** @brief
     *
     */
    int *live_d;

    /** @brief
     *
     */
    int dead_s;

} RuleSet;

#endif  /* RULESET_H_ */
