#include "..\inc\taskgrinch.h"

/* Prints "BON NADAL" and sleeps for x seconds */
void TaskGrinch(void* pdata)
{
  INT8U err;

  char visualiza_string[40] = "Hello from Grinch";
  char blank[40]="                                       \0";
  char visualiza_string_nadal[15][40]=
  {					"                 ",
                      "       OOOO      ",
                      "      OOOOOO     ",
                      "    OO      OO   ",
                      "  OO          OO ",
                      "  OO  XX  XX  OO ",
                      "  OO          OO ",
                      "  OO  ______  OO ",
                      "  OO  _|_|_|  OO ",
                      "  OO          OO ",
                      "    OOOOOOOOOO   ",
                      "                 ",
                      "  I'M CHRISTMAS' ",
                      "      HATER      ",
                      "                 "};

  int nadal_pos=10; //start VGA line to draw

/* local pointer declaration*/

  int *pMailBox_grinch = NULL;
  *pMailBox_grinch = nadal_pos;


  while (1)
  {
    OSSemPend(Semaphore,0,&err);
    alt_ucosii_check_return_code(err);

   printf("%s\n",visualiza_string);

    OSSemPost(Semaphore);
    alt_ucosii_check_return_code(err);

    //receive message from mailbox

    pMailBox_grinch = (int*) OSMboxPend(SharedMail,1000,&err);
    if(err == OS_ERR_NONE){
      nadal_pos = *pMailBox_grinch;
      OSSemPend(Semaphore,0,&err);
      alt_ucosii_check_return_code(err);
      printf("Mail is %d: new start position is %d\n",*pMailBox_grinch,nadal_pos);
      OSSemPost(Semaphore);
      alt_ucosii_check_return_code(err);
    }

    // Led_ON_All(red_LED_ptr);
    Led_OFF_All(LED_ptr);


    //clean text on black box
    for (int var = 3; var < 60; ++var) {
      OSSemPend(Semaphore,0,&err);
      alt_ucosii_check_return_code(err);
      VGA_text (40, var, blank,character_buffer);
      OSSemPost(Semaphore);
      alt_ucosii_check_return_code(err);
    }
    //creates picture
    for (int var = 0; var < 15; ++var) {
      OSSemPend(Semaphore,0,&err);
      alt_ucosii_check_return_code(err);
      VGA_text (50, nadal_pos+var, visualiza_string_nadal[var],character_buffer);
      OSSemPost(Semaphore);
      alt_ucosii_check_return_code(err);
    }
    
  OSTimeDlyHMSM(0, 0, 2, 0);

  }
}
