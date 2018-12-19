#ifndef IDSPACE_H_INCLUDED
#define IDSPACE_H_INCLUDED

/**
 *
 */
typedef struct
{
    /** @brief representation of an ID.
     *  TODO: make unique ID generator.
     */
     int id;

} Id;

/** @brief namespace for ids.
 *  IDSpace can be used to manage unique id's. It can dynamically resize itself as needed.
 *  New id's can be reserved using reserve() function and freed using release().
 *  id_array should not be modified externally because endanger the integrity of
 *  the IdSpace. Instead only dedicated functions should be used to request access
 *  to internal structures.
 */
typedef struct
{
    /** @brief Array containing alla ids.
     *
     */
    Id *id_array;

    /** @brief Size of the id_array.
     *
     */
    int id_size;

} IdSpace;

/** @brief Size of the id_array.
 *
 *  Creates new array with given size.
 */
IdSpace *IdSpace_new( int size );

/** @brief Free array
 *
 */
void IdSpace_free( IdSpace *ids );

/** @brief Free array
 *
 */
void IdSpace_add( Id *id );

/** @brief Free array
 *
 */
void IdSpace_remove( Id *id );

/** @brief Free array
 *
 */
void IdSpace_shrink( IdSpace *ids );

/** @brief Free array
 *
 */
void IdSpace_expand( IdSpace *ids );


#endif  /*  IDSPACE_H_INCLUDED */
