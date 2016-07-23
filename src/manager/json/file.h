#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../log.h"

/** @brief Count files in directory.
 *  Used to return count of files inside a directory. Counts files and/or directories,
 *  but ignores symlinks, etc. Mode is used to return files or directories or
 *  both.
 *
 * @param d_path Path to root directory.
 * @param mode   Mode to be used when counting files.
 * @return Number of files.
 */
int file_count( const char *d_path, int mode );

/** @brief Read all data from text file.
 *  Reads all data based on given file. Doesn't differentiate containment of the
 *  file in any way, but this function was created mainly for reading json files.
 *
 * @param file Path to file.
 * @return String containing file.
 */
char *file_read( const char *file );

/** @brief Write character string into a text file.
 *  Writes given character string into a file as such. Doesn't format given data
 *  in any way.
 *
 * @param str  Text to be written.
 * @param file Output file
 */
void file_write( char *str, const char *file );

#endif /* FILE_H_INCLUDED */
