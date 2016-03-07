#ifndef __JSM_H_
#define __JSM_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../view.h"
#include "jsmn.h"

typedef enum {
	/* Success */
	JSM_OK = 1,
	/* NULL pointer error */
	JSM_NULL = -3,
	/* File read failed */
	JSM_ERROR_FREAD = -1,
	/* Memory allocation failed */
	JSM_ERROR_ALLOC = -2
} jsmrtn_t;

/*
 * Updates cdefault values to file, creates if not exist
 */
jsmrtn_t jsm_default_model( view_model *model );

/*
 * Updates current to a settings file.
 */
jsmrtn_t jsm_update_model( view_model *model );

/*
 * Reads current values of model from a settings file.
 */
jsmrtn_t jsm_read_model( view_model *model );

/*
 * Read content of a file to a string.
 */
jsmrtn_t jsm_read_file( char **json, const char *file );

/*
 * Write content of a json string into a file.
 */
jsmrtn_t jsm_write_file( char *json, const char *file );

/*
 *
 */
jsmrtn_t jsm_val( char *rtn, const char *json, const char *key );

/*
 *
 */
jsmrtn_t jsm_obj( char *result, const char *full_json, int start, int end );

#endif /* __JSM_H_ */
