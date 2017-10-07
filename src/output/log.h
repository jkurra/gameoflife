#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

/** @brief Get current timestamp from system time.
 *
 *  @return current timestamp.
 */
char *log_timestamp();

/** @brief Get formatted log message with timestamp.
 *
 *  @param key Log identifier string.
 *  @param message String to format.
 *  @return current timestamp.
 */
char *log_message(const char *key, const char* message);

#endif  /* LOG_H_INCLUDED */
