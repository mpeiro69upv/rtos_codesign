/* atencion a interrupcion de pulsadores KEY en la DE1Soc */

#include "..\inc\isr.h"

void pushbutton_isr()
{
OSIntEnter(); /* Inform the OS that we are starting an ISR */

  char vga_msg[60];
    
  INT8U key_pressed;

  //local variable to store position message for ISR
  static int PositionMessage_isr=10;
  int * pMessage_isr= &PositionMessage_isr;
  

  /* read the KEY interrupt register to determine which KEY was pressed */
  key_pressed = *(KEY_ptr + 3);   

  /* clear the interrupt */
  *(KEY_ptr + 3) = key_pressed;    

  /* post the semaphore for the corresponding task */
  if (key_pressed & 0x1)   // KEY0 pressed
  {
    snprintf(vga_msg, sizeof(vga_msg), "%02d   KEY0 Interruption", line);
    Print_VGA(vga_msg, &line);
  }
  if (key_pressed & 0x2)   // KEY1 pressed
  {
    snprintf(vga_msg, sizeof(vga_msg), "%02d   KEY1 Interruption", line);
    Print_VGA(vga_msg, &line);
    OSFlagPost(EventFlag,0x01,OS_FLAG_SET, &error);
    alt_ucosii_check_return_code(error);
  }
  if (key_pressed & 0x4)   // KEY2 pressed
  {
    PositionMessage_isr+=1;
    snprintf(vga_msg, sizeof(vga_msg), "%02d   KEY2 Interruption", line);
    Print_VGA(vga_msg, &line);
  }
  if (key_pressed & 0x8)   // KEY3 pressed
  {
    PositionMessage_isr-=1;
    snprintf(vga_msg, sizeof(vga_msg), "%02d   KEY3 Interruption", line);
    Print_VGA(vga_msg, &line);
  }

  //saturation of PositionMessage to avoid writing outside VGA limits
  if (PositionMessage_isr<3) PositionMessage_isr=3;
  if (PositionMessage_isr>45) PositionMessage_isr=45;
  
  OSMboxPost(SharedMail, (void *) pMessage_isr);

OSIntExit(); /* Inform the OS that we are leaving the ISR */
}

/* PS2 keyboard interrupt service routine */

/*
 * Keyboard ISR. Read key pressed and send it to a queue.
 * Key code is extracted after release a key, so first the code 0xF0 (release) is received.
 * Once the code of release 0xF0 is received then key code is saved on a queue.
 * Size of secret code is 4: 3 numbers or keys and INTRO code (0x5A).
 * If user press more than 4 keys queue is flush and a BAD CODE message is sent.
 *
 */

 void keyboard_isr(){
	OSIntEnter();
  INT8U Keycode;
  INT8U Rvalid;
  INT8U err;
  static	INT8U Release=0;

  static INT8U i=0;
  //local buffer for messages in ISR
  static MSG_DATA_PS2 msg_isr[QUEUE_SIZE];
// static allocates memory only once
// instead of doing it each time the ISR is executed
// which would be inefficient and could lead to fragmentation
// of the memory over time.
// in addition, dynamic memory allocation is not recommended in ISRs
// due to potential delays and unpredictability associated with memory allocation routines.

// Using a static array ensures that memory is allocated at compile time
// and is readily available when the ISR is invoked.
  
	alt_irq_disable(PS2_KEY_IRQ);
	Rvalid=((*keyboard_ptr)>>12)&0x08; //check if data is valid
	if (Rvalid){
		Keycode=(*keyboard_ptr)&0xFF; //read the value

		switch (Keycode) {
			case 0xAA: //code received from keyboard when is connected (5V)
				printf("Keyboard Connected...\n");
				Release=0;
				OSTimeSet(0); //reset time counter
				break;
			case 0xf0: //code of release
				Release=1;
				break;
			default:
				if (Release){

					i = (i+1) % QUEUE_SIZE;
					msg_isr[i].time=OSTimeGet();
					msg_isr[i].key_pressed=Keycode;
					msg_isr[i].count_key=i;
					printf("Value on keyboard is %x\n",(INT8U)msg_isr[i].key_pressed);
					err=OSQPost(MessageQueue,(void *)&msg_isr[i]);
					alt_ucosii_check_return_code(err);

					Release=0;
				}
				break;
		}
	}
	else{
		printf("Keyboard data undefined\n");
	}

	alt_irq_enable(PS2_KEY_IRQ);

	OSIntExit();
}


