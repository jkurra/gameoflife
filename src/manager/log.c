#include "log.h"

char *log_timestamp()
{
    time_t rawtime;
    struct tm * timeinfo;
    static char result1[26];
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    sprintf(result1, "%d-%d-%d %.2d:%.2d:%.2d",
        1900 + timeinfo->tm_year, timeinfo->tm_mon+1,
        timeinfo->tm_mday, timeinfo->tm_hour,
        timeinfo->tm_min, timeinfo->tm_sec
    );

    return result1;
}
