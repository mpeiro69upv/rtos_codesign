#ifndef PRACT1_RTOS_H__ 
#define PRACT1_RTOS_H__

/* declaration of functions from pract1_rtos.c */

/* Definition of Task Priorities */

#define TASK1_PRIORITY      1
#define TASK2_PRIORITY      2
#define TASK3_PRIORITY      3
#define TASK4_PRIORITY      4
#define TASKGRINCH_PRIORITY 5
#define TASKNADAL_PRIORITY  6
#define TASKCODE_PRIORITY   7
#define TASKFLAGS_PRIORITY  8
#define TASK_SWITCH_PRIORITY 9

/* public declaration of peripherals */
extern volatile int 	* LED_ptr;
extern volatile int 	* HEX2_HEX0_ptr;
extern volatile int 	* HEX5_HEX3_ptr;
extern volatile int 	* KEY_ptr;
extern volatile int 	* SW_switch_ptr;
extern volatile short   * pixel_buffer;
extern volatile char 	* character_buffer;
extern volatile int	    * keyboard_ptr;


/* include ucos basic libraries */
#include <stdio.h>
#include <stdlib.h>
#include "includes.h"


extern INT8U error;


/* include header files for the tasks */
#include "App_SW/inc/task1.h"
#include "App_SW/inc/task2.h"
#include "App_SW/inc/task3.h"
#include "App_SW/inc/task4.h"
#include "App_SW/inc/taskgrinch.h"
#include "App_SW/inc/tasknadal.h"
#include "App_SW/inc/isr.h"
#include "App_SW/inc/init.h"
#include "App_SW/inc/alt_ucosii_simple_error_check.h"
#include "App_SW/inc/taskcode.h"
#include "App_SW/inc/taskflags.h"
#include "App_SW/inc/tasksw.h"


/*include header files from peripherals */
#include "Base_SW/inc/led.h"
#include "Base_SW/inc/vga.h"

#endif // PRACT1_RTOS_H__
