#include "..\inc\tasknadal.h"

/* Prints "BON NADAL" and sleeps for x seconds */
void TaskNadal(void* pdata)
{
  char visualiza_string[40] = "Hello from NADAL";
  char blank[40]="                                      \0";

  char visualiza_string_nadal[15][40]=
  {                   "                 ",
                      "        X        ",
                      "       XXX       ",
                      "      XXXXX      ",
                      "     XXXXXXX     ",
                      "    XXXXXXXXX    ",
                      "   XXXXXXXXXXX   ",
                      "  XXXXXXXXXXXXX  ",
                      "       XXX       ",
                      "                 ",
                      " MERRY CHRISTMAS ",
                      "    BON NADAL    ",
                      "                 ",
                      "                 ",
                      "                 "};

  int nadal_pos=10;

  while (1)
  {
    printf("%s\n",visualiza_string);

    
    Led_ON_All(LED_ptr);

    //clean text on black box
    for (int var = 3; var < 60; ++var) {
      VGA_text (40, var, blank,character_buffer);
    }

    for (int var = 0; var < 15; ++var) {
      VGA_text (50, nadal_pos+var, visualiza_string_nadal[var],character_buffer);
    }

   OSTimeDlyHMSM(0, 0, 4, 0);
    
  }
}


