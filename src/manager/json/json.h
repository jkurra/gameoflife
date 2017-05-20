#ifndef __JSON_H_
#define __JSON_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "jsmn.h"

#define KEYPAIR 0
#define OBJECT  1

/** @brief Base JsonObject class.
 *
 */
typedef struct
{
    /** @brief
     *
     */
    int type;

} JsonToken;

/** @brief Json value-keypair structure.
 *
 */
typedef struct
{
    /** @brief
     *
     */
    JsonToken base;
    /* Key-identifier of the value. Refer to json structure guide. */
    /** @brief
	 *
     */
    char *key;
    /* Value of the keypair as "string". Other types are not supported.*/
    /** @brief
	 *
     */
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
    /** @brief
     *
     */
    JsonToken base;

    /** @brief
	 *
     */
    char *main_object;

    /** @brief
     *
     */
    char *object_id;

    /** @brief
	 *
     */
    JsonKeypair **values;

    /** @brief
     *
     */
    int  values_size;

    /** @brief
	 *
     */
    int objects_size;

    /** @brief
     *
     */
    struct json_o **objects;

} JsonObject;

/** @brief Parse json object from string.
 *
 *  Parses json from given string. String is a properly formatted json object.
 *  NULL value intializes empty json string (basically "{}") and all member
 *  values are set to initial values. New values and objects may then be added
 *  later. TODO: Add checks if json is malformed or missing identifiers.
 *
 *  @param json String representation of json object.
 */
JsonObject *json_parse( const char *json );

/** @brief Free json object and all its member values and objects.
 *
 */
void json_free( JsonObject *json );

/** @brief Add value or object to existing object.
 *
 *  Add given object to another json-object. parameter to_add is valid json
 *  object. If object is malformed, it will be discarded.
 *
 *  @param main_object Object which is used to add another object into.
 *  @param to_add   Object to be added to main_object.
 *
 */
void json_add( JsonObject *json, JsonToken *to_add );

/** @brief Remove value or object from existing object.
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

void json_add_value( JsonObject *json, JsonKeypair *to_add );

/** @brief Find value or object from given object.
 *
 *  Searches for keypair or object with matching key-identifier. If one is found
 *  pointer to it is returned, if none is found returned pointer is set NULL.
 *  Returned pointer doesn't have to be freed, since it is part of JsonObject and
 *  is freed when json_free is called. Attempting to free it will result in
 *  double free.
 *
 *  @param json String representation of the json object.
 *  @param key  Identifier of the object or keypair to be searched.
 */
JsonToken *json_find( JsonObject *json, const char *key );

/** @brief Create new keypair, from two strings.
 *
 *  Allocates new keypair, using parameters. Key-value pair consists of two
 *  strings. Keypair must be deallocated using appropriate free() function.
 *  TODO: rename and rethink structure.
 */
JsonKeypair *json_keypair_create( const char *key, const char *value );

#endif /* __JSON_H_ */
