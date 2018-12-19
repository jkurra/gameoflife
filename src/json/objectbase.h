#ifndef OBJECTBASE_H_INCLUDED
#define OBJECTBASE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "jsonvalue.h"
#include "jsmn/jsmn.h"

/** @brief
 *
 */
typedef struct
{
    /** @brief
     *
     */
    JsonValue **values;

    /** @brief
     *
     */
    int values_size;

} ObjectBase;

/** @brief
 *
 */
ObjectBase *ObjectBase_new();

/** @brief
 *
 */
void ObjectBase_free( ObjectBase *baseObject );

/** @brief
 *
 */
ObjectBase *ObjectBase_create( const char *objectString );

/** @brief
 *
 */
JsonValue *ObjectBase_get( ObjectBase *baseObject, const char *key );

/** @brief
 *
 */
void ObjectBase_add( ObjectBase *baseObject, JsonValue *value );

/** @brief
 *
 */
char *ObjectBase_to_string( ObjectBase *baseObject );

#endif  /* OBJECTBASE_H_INCLUDED */
