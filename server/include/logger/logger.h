#ifndef LOGGER_H
#define LOGGER_H 

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define ERROR "error"
#define SUCCESS "success"

// ( définition dans le programme )
extern int logger(char * type, const char *fmt, ...);
// afficher un texte dans la sortie du logger
int logger(char * type, const char *fmt, ...);
// initialiser la sortie du logger
void init_logger(int dout);

#endif // LOGGER_H