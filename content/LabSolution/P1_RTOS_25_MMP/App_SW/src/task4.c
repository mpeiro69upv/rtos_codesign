
/* include necessary headers */
#include "..\inc\task4.h"

/* Prints "Hello World" and sleeps for five seconds */
void task4(void* pdata)
{
  char vga_msg[60];
  while (1)
  { 
    Led_OFF_Some(LED_ptr,8,2);
    
    /* critical section */
    OSSemPend(Semaphore, 0, NULL);

    printf("Hello from task4\n");
    snprintf(vga_msg, sizeof(vga_msg), "%02d   Hello from task4", line);
    Print_VGA(vga_msg, &line);
    
    OSSemPost(Semaphore);
    /* end of critical section */
    
    OSTimeDlyHMSM(0, 0, 5, 0);
  }
}