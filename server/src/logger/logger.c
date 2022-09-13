#include "logger/logger.h"

static int log; // = STDOUT_FILENO;
pthread_mutex_t log_mut = PTHREAD_MUTEX_INITIALIZER;

/**
 *
 * fonction logger type:string, format:string, ...:*
 *
 * écrire dans le logger
 * 
 * 
 */
int logger(char *type, const char *fmt, ...)
{
    pthread_mutex_lock(&log_mut);
    
    if (log == STDOUT_FILENO)
    {
        if (strcmp(type, ERROR) == 0)
        {
            dprintf(log, "[\033[0;31m%s\033[0m] ", type);
        }
        else if (strcmp(type, SUCCESS) == 0)
        {
            dprintf(log, "[\033[0;32m%s\033[0m] ", type);
        }
        else
        {
            dprintf(log, "[\033[0;34m%s\033[0m] ", type);
        }
    }
    else
    {
        dprintf(log, "[%s] ", type);
    }
    va_list args;
    va_start(args, fmt);
    int rc = vdprintf(log, fmt, args);
    va_end(args);
    dprintf(log, "\n");

    pthread_mutex_unlock(&log_mut);
    return rc;
}

void init_logger(int dout)
{
    log = dout;
    logger("logger", "init_logger (%d)", dout);
}