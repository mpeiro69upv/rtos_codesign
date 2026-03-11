#ifndef INIT_H__
#define INIT_H__

/* include main project library */
#include "..\..\pract1_rtos.h"

/* declare de functions from init.c */
void Init_App(void);
void Print_VGA(char visualiza_string[15], int* line);

/* extern public variables */
extern int line;

/* extern UCOS Utilities */
//extern OS_EVENT* Semaphore;

#endif // INIT_H__

