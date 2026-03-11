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
extern OS_EVENT* Semaphore;
extern OS_EVENT* SharedMail;
extern OS_FLAG_GRP* EventFlag;
extern OS_FLAGS FlagQuery;



extern OS_EVENT* MessageQueue;

/* local structure of data */
#define QUEUE_SIZE 4 
typedef struct msg_data{
  int time;
  int key_pressed;
  int count_key;
}MSG_DATA_PS2;



#endif // INIT_H__

