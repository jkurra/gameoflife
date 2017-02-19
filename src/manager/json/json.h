#ifndef __JSON_H_
#define __JSON_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "jsmn.h"

/** @brief Json value-keypair structure.
 *
 */
typedef struct
{
    /* Key-identifier of the value. Refer to json structure guide. */
    char *key;
    /* Value of the keypair as "string". Other types are not supported yet.*/
    char *value;

} json_kpr;

/** @brief Json object structure.
 *
 *  Represents a json object, which may contain key-value pairs and other objects.
 *  All changes and data requests must be done using appropriate functions.
 *
 */
typedef struct json_o
{
    char *main_object;
    char *object_id;

    json_kpr **values;
    int  values_size;

    int objects_size;
    struct json_o **objects;
} json_ob;

/** @brief Create new keypair, from two strings.
 *
 *  Allocates new keypair, using parameters. Key-value pair consists of two
 *  strings. Keypair must be deallocated using appropriate free() function.
 *
 *
 */
json_kpr *json_keypair_create( const char *key, const char *value );

/** @brief Free json keypair and its members.
 *
 *
 */
void json_keypair_free( json_kpr *keypair );

/** @brief Create new json-object from string.
 *
 *  Creates new json object from existing string, if string is NULL, Creates
 *  empty object. If json data is corrupted or not a json string function
 *  returns NULL pointer.
 *
 *  @json   Contains full json string, or NULL pointer.
 *  @return newly allocated json-object.
 */
json_ob *json_create( const char *json );

/** @brief Free json object and all its member values and objects.
 *
 */
void json_free( json_ob *json );

/** @brief Add object to existing object.
 *
 *  Add given object to another json-object. parameter to_add is valid json
 *  object. If object is malformed, it will be discarded.
 *
 *  @param main_object Object which is used to add another object into.
 *  @param to_add   Object to be added to main_object.
 *
 */
void json_add_value( json_ob *json, json_kpr *to_add );

/** @brief Add object to existing object.
 *
 *  Add given object to another json-object. parameter to_add is valid json
 *  object. If object is malformed, it will be discarded.
 *
 *  @param main_object Object which is used to add another object into.
 *  @param to_add   Object to be added to main_object.
 *  TODO: Not yet implemented.
 */
void json_rem_value( json_ob *json, json_kpr *to_rem );

/** @brief Add object to existing object.
 *
 *  Add given object to another json-object. parameter to_add is valid json
 *  object. If object is malformed, it will be discarded.
 *
 *  @param main_object Object which is used to add another object into.
 *  @param to_add   Object to be added to main_object.
 *
 */
void json_add_object( json_ob *main_object, json_ob *to_add );

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
void json_rem_object( json_ob *main_object, const char *to_remove );

/** @brief Find from json, using Key-identifier.
 *  Combine these two if possible.
 *
 */
json_kpr *json_find_value( json_ob *json, const char *key );
json_ob  *json_find_object( json_ob *json, const char *key );

#endif /* __JSON_H_ */
