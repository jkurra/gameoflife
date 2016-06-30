#ifndef __JSM_H_
#define __JSM_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/gl.h>

#include "../../mvc/view.h"
#include "jsmn.h"

/* Json functions */

/** @brief Pull single token from json string.
 *
 */
char *json_token( char *json, int start, int end );

/** @brief Pull json value from object.
 *
 */
char *json_value( char *json, char *key, jsmntype_t type );

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
int jsm_atoi( const char *json, char *key );

#endif /* __JSM_H_ */
