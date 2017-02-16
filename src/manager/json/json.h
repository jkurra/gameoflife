#ifndef __JSON_H_
#define __JSON_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "jsmn.h"
#include "../../output/log.h"

/** @brief Json value-keypair structure.
 *  TODO: Not yet in use.
 */
typedef struct
{
    /* Key-identifier of the value. Refer to json structure guide. */
    char *key;
    /* Value of the keypair as "string". Other types are not supported yet.*/
    char *value;

} json_kpr;

/** @brief Create new keypair, from two strings.
 *
 *  Allocates new keypair, using parameters. Key-value pair consists of two
 *  strings. Keypair must be deallocated using appropriate free() function.
 *
 *
 */
json_kpr *json_keypair_create( const char *key, const char *pair );

/** @brief Free json keypair and its members.
 *
 *
 */
void json_keypair_free( json_kpr *keypair );

/** @brief Json object structure.
 *
 *  Represents a json object, which may contain key-value pairs and other objects.
 *  All changes and data requests must be done using appropriate functions.
 *
 */
typedef struct
{
    char **objects;
    int  objects_size;

    char **values;
    int  values_size;

} json_ob;

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

char *json_get( json_ob *object, const char *key );

/** @brief Free json object and all its member values and objects.
 *
 */
void json_free( json_ob *json );

/** @brief Add key-value pair to json-object.
 *
 *  Adds given key-value pair to "values" array in json_ob. Doesn't check validity
 *  of the json_keypair. Only used to add values, not objects.
 *
 */
void json_add_value( json_ob *json, const char *keypair);

/** @brief Remove key-value pair to json-object.
 *
 *  Removes key-value pair from object, based on given key.
 *
 */
void json_rem_value( json_ob *json, const char *key);

/** @brief Add object to existing object.
 *
 *  Add given object to another json-object. parameter to_add is valid json
 *  object. If object is malformed, it will be discarded.
 *
 *  @param main_object Object which is used to add another object into.
 *  @param to_add   Object to be added to main_object.
 *  TODO: Not yet implemented.
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

/** @brief Return full representation of the json as a string.
 *
 */
char *json_to_string( json_ob *json );


/** @brief Pull single token from json string.
 *
 *  Pulls token from json string based on given start and end values. Only for
 *  Getting tokens, doesn't check contents so validity is up to user. Returned
 *  value must be freed using standard free().
 *
 *  @json   Contains full json string.
 *  @start  Index of the first character to be added.
 *  @end    Index of the last character to be added.
 *  @return newly allocated token.
 */
char *json_tok( const char *json, int start, int end );


/** @brief Construct a json key-value pair as a c-string.
 *
 *  Creates string containing json key-value pair of given values. Basically Adds
 *  all necessary characters and allocates space for created string. Comma may be
 *  added to the end of the string. This is because this function is often used
 *  to construct json-objects. Returned value must be freed using standard free()
 *  function.
 *
 *  @value  value as character string, may be any type.
 *  @key    Identifie that may be used to find this value later.
 *  @comma  1 to add comma, 0 to not add.
 *  @return json keypair containing all necessary characters.
 */
char *json_keypair( char *value, char *key, int comma );

char *json_val( const char *json, char *key, jsmntype_t type );

#endif /* __JSON_H_ */
