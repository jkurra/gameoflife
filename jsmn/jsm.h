#ifndef __JSM_H_
#define __JSM_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../view.h"
#include "jsmn.h"

/* Json functions */

/* @brief Construct a json key-value pair.
 *
 */
char *jsm_keypair( char *value, char *key, int comma );

/* @brief Construct json object from valuepair array.
 *
 */
char *jsm_jobj( int indent,  int size, char *array[size] );

/* @brief Read token from json string.
 *
 */
char *jsm_jtok( char *json, int start, int end );

/* @brief Read value based on given key from json.
 *
 */
char *jsm_jval( char *json, char *key, jsmntype_t type );

/* File IO functions */

/*
 * Read content of a file to a string.
 */
char *jsm_fread( const char *file );

/*
 * Write content of a json string into a file.
 */
int jsm_fwrite( char *json, const char *file );

/*
 * Write content of a json string into a file.
 */
void jsm_read_commons( commons_model *model, const char *pref_path );

/*
 * Write content of a json string into a file.
 */
void jsm_write_commons( commons_model *model, const char *pref_path );

/* Value cast functions */

/* @brief Cast integer into string
 *
 */
char *jsm_itoa( int value );

/* @brief Cast value from json to Integer.
 *
 */
int jsm_atoi( const char *json, const char *key );

#endif /* __JSM_H_ */
