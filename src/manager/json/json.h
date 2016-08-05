#ifndef __JSON_H_
#define __JSON_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "jsmn.h"
#include "../log.h"

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

/** @brief Pull json value from object.
 *
 *  Pulls value from json object, using key as identifier.
 */
char *json_val( const char *json, char *key, jsmntype_t type );

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

/** @brief Creates json object from key-value pairs.
 *
 */
char *json_obj( int indent,  int size, char *array[size] );

/* @brief Cast value from json to Integer.
 *
 */
int json_atoi( const char *json, char *key );

#endif /* __JSON_H_ */
