#ifndef __JSON_H_
#define __JSON_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "jsmn.h"

#define KEYPAIR 0
#define OBJECT  1

/** @brief Json value-keypair structure.
 *
 */
typedef struct
{
    int type;

} JsonToken;

/** @brief Json value-keypair structure.
 *
 */
typedef struct
{
    JsonToken base;
    /* Key-identifier of the value. Refer to json structure guide. */
    char *key;
    /* Value of the keypair as "string". Other types are not supported yet.*/
    char *value;

} JsonKeypair;

/** @brief Json object structure.
 *
 *  Represents a json object, which may contain key-value pairs and other objects.
 *  All changes and data requests must be done using appropriate functions.
 *
 */
typedef struct json_o
{
    JsonToken base;

    char *main_object;
    char *object_id;

    JsonKeypair **values;
    int  values_size;

    int objects_size;
    struct json_o **objects;

} JsonObject;

/** @brief Free json object and all its member values and objects.
 *
 */
JsonObject *json_parse( const char *json );

/** @brief Free json object and all its member values and objects.
 *
 */
void json_free( JsonObject *json );

/** @brief Add object to existing object.
 *
 *  Add given object to another json-object. parameter to_add is valid json
 *  object. If object is malformed, it will be discarded.
 *
 *  @param main_object Object which is used to add another object into.
 *  @param to_add   Object to be added to main_object.
 *
 */
void json_add( JsonObject *json, JsonToken *to_add );

/** @brief Remove object from existing object.
 *
 *  Remove object from main_object using object identifier. Each object in
 *  main_object is checked to see if id-string is same as to_remove.
 *  TODO: Objects must have an unique id-name.
 *
 *  @param main_object
 *  @param to_rem
 *  TODO: Not yet implemented.
 */
void json_rem( JsonObject *json, const char *to_remove );

/** @brief Remove object from existing object.
 *
 *  Remove object from main_object using object identifier. Each object in
 *  main_object is checked to see if id-string is same as to_remove.
 *  TODO: Objects must have an unique id-name.
 *
 *  @param main_object
 *  @param to_rem
 *  TODO: Not yet implemented.
 */
JsonToken *json_find( JsonObject *json, const char *key );

/** @brief Create new keypair, from two strings.
 *
 *  Allocates new keypair, using parameters. Key-value pair consists of two
 *  strings. Keypair must be deallocated using appropriate free() function.
 */
JsonKeypair *json_keypair_create( const char *key, const char *value );

#endif /* __JSON_H_ */
