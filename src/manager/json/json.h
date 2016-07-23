#ifndef __JSM_H_
#define __JSM_H_

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "jsmn.h"
#include "../log.h"

/** @brief Pull single token from json string.
 *
 */
char *json_token( char *json, int start, int end );

/** @brief Pull json value from object.
 *
 */
char *json_val( const char *json, char *key, jsmntype_t type );

/** @brief Construct a json key-value pair as a c-string.
 *
 */
char *json_keypair( char *value, char *key, int comma );

/** @brief Constuct a full json object based on key-value pairs.
 *
 */
char *json_object( int indent,  int size, char *array[size] );

/** @brief Write a given json string to a physical file.
 *
 */
void json_write( char *json, const char *file );

/** @brief Read contents of a file to a string.
 *
 */
char *json_read( const char *file );

char *json_obj(  int indent,  int size, char *array[size] );

/* File IO functions */

/*
 * Read content of a file to a string.
 */
char *jsm_fread( const char *file );

/*
 * Write content of a json string into a file.
 */
int jsm_fwrite( char *json, const char *file );



/* Value cast functions */

/* @brief Cast integer into string
 *
 */
char *jsm_itoa( int value );

/* @brief Cast value from json to Integer.
 *
 */
int jsm_atoi( const char *json, char *key );

#endif /* __JSM_H_ */
