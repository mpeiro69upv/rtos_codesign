/* include necessary headers */
#include "..\inc\task3.h"

/* Prints "Hello World" and sleeps for one second */
void task3(void* pdata)
{
  char vga_msg[60];
  while (1)
  { 
    Led_ON_Some(LED_ptr,8,2);

    /* critical section */
    OSSemPend(Semaphore, 0, NULL);

    printf("Hello from task3\n");
    snprintf(vga_msg, sizeof(vga_msg), "%02d   Hello from task3", line);
    Print_VGA(vga_msg, &line);
    
    OSSemPost(Semaphore);

    /* end of critical section */

    OSTimeDlyHMSM(0, 0, 1, 0);
  }
}