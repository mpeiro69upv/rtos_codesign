#include "..\inc\taskflags.h"

void TaskFlags()
{

  char texto[80];

  while(1)
  {
  
    OSSemPend(Semaphore,0,&error);
    alt_ucosii_check_return_code(error);
    printf("Hello from TaskFlags\n");
    OSSemPost(Semaphore);

    OSTimeDlyHMSM(0,0,1,0); // Delay for 1 seconds
    
    FlagQuery = OSFlagAccept(EventFlag,0x07,OS_FLAG_WAIT_SET_ALL, &error);
    //alt_ucosii_check_return_code(error);
    OSSemPend(Semaphore,0,&error);
    alt_ucosii_check_return_code(error);
    printf("Flags status is %x\n", (int)FlagQuery);    
    OSSemPost(Semaphore);
    

    if(FlagQuery == 0x07)
    {
      sprintf(texto, "Codigo Correcto y KEY1 pulsado y SW8 activo... volvamos a empezar!");
      
      // Clear all flags
      OSFlagPost(EventFlag,0x07,OS_FLAG_CLR, &error);
      alt_ucosii_check_return_code(error);
    } else {
      sprintf(texto,"Valor de los flags es %x", (int)FlagQuery);
    }
    OSSemPend(Semaphore,0,&error);
    alt_ucosii_check_return_code(error);

    VGA_Clean_Full_Lines(50,52,character_buffer);
    VGA_text(10,50,texto,character_buffer);

    OSSemPost(Semaphore);
    
    
  }
}
