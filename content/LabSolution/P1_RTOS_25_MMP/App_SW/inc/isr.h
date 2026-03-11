#ifndef ISR_H
#define ISR_H

/* include main project library */
#include "..\..\pract1_rtos.h"

/* declare functions from isr.c */
void pushbutton_isr();
void keyboard_isr();

#endif  // ISR_H