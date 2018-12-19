#ifndef JSONVALUE_H_INCLUDED
#define JSONVALUE_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "jsmn/jsmn.h"

/** @brief
 *
 */
enum ValueType { STRING, OBJECT, NUMBER };

/** @brief
 *
 */
typedef struct {

    /** @brief
     *
     */
    enum ValueType type;

    /** @brief
     *
     */
    char *key;

    /** @brief
     *
     */
    char *string;

    /** @brief
     *
     */
    char *obj;

    /** @brief
     *
     */
    int number;

} JsonValue;

/** @brief
 *
 */
JsonValue *JsonValue_new_string( const char *key, const char *string );

/** @brief
 *
 */
JsonValue *JsonValue_new_object( const char *key, const char *string );

/** @brief
 *
 */
JsonValue *JsonValue_new_number( const char *key, int number );

/** @brief
 *
 */
JsonValue *JsonValue_new_boolean( const char *key, int boolean );

/** @brief
 *
 */
void JsonValue_free(JsonValue *value);

/** @brief
 *
 */
enum ValueType JsonValue_type( JsonValue *value );

/** @brief
 *
 */
char *JsonValue_key( JsonValue *value );

/** @brief
 *
 */
JsonValue *JsonValue_copy( JsonValue *value );

/** @brief
 *
 */
char *JsonValue_to_string( JsonValue *value );

#endif  /* JSONOBJECT_H_INCLUDED */
