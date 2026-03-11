/*
 * taskcode.c
 *
 *  Created on: 13 de may. de 2024
 *      Author: mpeiro
 */



#include "..\inc\taskcode.h"
#define PRINT_DEBUG

void TaskCode()
{

  MSG_DATA_PS2* msg_rx; //pointer to message received from queue

  static INT8U Count_keys_received=0;

  INT8U error;

  INT32U CodeReceived	=0;
  INT32U SecretCode	=0x69727a5a;  //1(69),2(72),3(7A),INTRO(5A) if keypad used for numbers
  INT32U SecretCode2=0x161e265a;  //1(16),2(1e),3(26),INTRO(5A) if keyboard used for numbers

  while(1)
  {

    OSTimeDlyHMSM(0,0,1,0);

    msg_rx=(MSG_DATA_PS2*)OSQPend(MessageQueue,0,&error);
    alt_ucosii_check_return_code(error);


#ifdef PRINT_DEBUG
    printf("Message received is: Time=%d ms, KeyCode=%x, KeyCount=%d\n",msg_rx->time,msg_rx->key_pressed,msg_rx->count_key);
#endif

    Count_keys_received=Count_keys_received+1;

    CodeReceived=CodeReceived<<8|msg_rx->key_pressed; //creating the 32bits code

    // if INTRO is pressed flush the queue
    if (msg_rx->key_pressed==0x5A){
      OSQFlush(MessageQueue);
      Count_keys_received=0;
    }
#ifdef PRINT_DEBUG
    printf("Secret Code received is %x\n",(int)CodeReceived);
    printf("Count_Keys_received is %x\n",(int)Count_keys_received );
#endif
    //If SecretCode (1-2-3) is received and 4 keys were pressed -> CORRECT CODE
    if (((CodeReceived==SecretCode) || (CodeReceived==SecretCode2))&&(Count_keys_received==0))
    {

      VGA_Clean_Full_Lines(20,23,character_buffer);

      printf("YOU GET THE CODE!!!\n");

      VGA_text(10+15,20,"  OH YES BABY   ",character_buffer);
      VGA_text(8+15,22, "YOU GET THE CODE",character_buffer);

      OSQFlush(MessageQueue);
      CodeReceived=0;
      Count_keys_received=0;

      OSFlagPost(EventFlag,0x02,OS_FLAG_SET, &error);
      alt_ucosii_check_return_code(error);

    }
    else
    {

      if (((Count_keys_received<4)&&(msg_rx->key_pressed!=0x5A))){

        VGA_text(10+15,20,"    HEY BABY    ",character_buffer);
        VGA_text(8+15,22, "   WRITING CODES",character_buffer);

      }else{					//even if INTRO is pressed CodeReceived gets 0
        printf("WRONG CODE!!! Code Received: %x\n", (int)CodeReceived);
        CodeReceived=0;
        Count_keys_received=0;
        OSQFlush(MessageQueue);

        VGA_text(10+15,20,"   SORRY BABY   ",character_buffer);
        VGA_text(10+15,22,"   WRONG  CODE  ",character_buffer);

        OSFlagPost(EventFlag,0x02,OS_FLAG_CLR, &error);
        alt_ucosii_check_return_code(error);

      }
    }
  }
}
