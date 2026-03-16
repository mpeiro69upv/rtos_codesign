/*
 * taskbart.c
 *
 *  Created on: 13 de may. de 2024
 *      Author: mpeiro
 */


#include "..\inc\taskbart.h"

/* Prints "Bart Simpson" and sleeps for x seconds */
void TaskBart(void* pdata)
{
	char visualiza_string[40] = "Hey Man!!";
	char blank[36]="                                  \0";

	char visualiza_string_bart[15][40]=
	{					"                 ",
            "    |\\/\\/\\/|     ",
            "    |      |     ",
            "    |      |     ",
            "    | (o)(o)     ",
            "    C      _)    ",
            "    | ,___|      ",
            "    |   /        ",
            "   /____\\        ",
            "  /      \\       ",
						"                 ",
						" EAT MY SHORTS!  ",
						"                 ",
						"                 ",
						"                 "};

	int bart_pos=10;
  while (1)
  {
	  printf("%s\n",visualiza_string);

	  OSTimeDlyHMSM(0, 0, 4, 0);
    Led_ON_All(LED_ptr);

    //clean text on black box
    for (int var = 3; var < 60; ++var) {
      VGA_text (40, var, blank,character_buffer);
    }

    for (int var = 0; var < 15; ++var) {
      VGA_text (50, bart_pos+var, visualiza_string_bart[var],character_buffer);
    }
  }
}


