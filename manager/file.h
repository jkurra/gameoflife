#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include <dirent.h>
#include <string.h>

/** @brief Count files in directory.
 *
 */
int file_count( const char *d_path, int mode );

#endif /* FILE_H_INCLUDED */
