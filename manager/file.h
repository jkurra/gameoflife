#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/** @brief Count files in directory.
 *
 */
int file_count( const char *d_path, int mode );

/** @brief Count files in directory.
 *
 */
char *file_read( const char *file );

/** @brief Count files in directory.
 *
 */
void file_write( char *str, const char *file );


#endif /* FILE_H_INCLUDED */
