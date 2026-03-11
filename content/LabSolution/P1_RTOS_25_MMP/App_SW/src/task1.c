/* include necessary headers */

#include "..\inc\task1.h"


/* Prints "Hello World" and sleeps for three seconds */
void task1(void* pdata)
{

  char vga_msg[60];
  while (1)
  { 
    Toggle_Led(LED_ptr,0);
    
    /* critical section */
    OSSemPend(Semaphore, 0, NULL);

    printf("Hello from task1\n");
    snprintf(vga_msg, sizeof(vga_msg), "%02d   Hello from task1", line);
    Print_VGA(vga_msg, &line);
    
    OSSemPost(Semaphore);
    /* end of critical section */

    Toggle_Led(LED_ptr,0);
    OSTimeDlyHMSM(0, 0, 3, 0);
  }
}