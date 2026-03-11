/*
 * led.c
 *
 *  Created on: 7 de dic. de 2023
 *      Author: mpeir
 */

#include "..\inc\led.h"
#define MAX_NUM_LED 9
/*****************************************************************
 *                   FUNCIONES DE MANEJO DE LEDS
 ****************************************************************/

int Led_ON (volatile int * ptr_led, int i)
{
	if ((i<0) || (i>MAX_NUM_LED))
	{
		return 0;
	}
	else
	{
		*(ptr_led) |= (0x00000000 | (1 << i));	//switch on LED-i
		return 1;
	}
}

int Led_OFF (volatile int * ptr_led, int i)
{
	if (( i<0) || (i>MAX_NUM_LED))
	{
		return 0;
	}
	else
	{
		*(ptr_led) &= (0xFFFFFFFF) ^ (1 << i);	//switch off LED-i

		return 1;
	}
}

/* Toggle_Led:
 * Toggle the specified LED (flip its state).
 * If the LED index is out of range, the function returns 0.
 */
int Toggle_Led (volatile int * ptr_led, int i)
{

	if ((i<0) || (i>MAX_NUM_LED)) 
		{
			return 0;
		}
		else
		{
			*(ptr_led) ^= (0x00000000 | (1 << i)); //switch LED-i
			return 1;
		}
}

void Led_OFF_All (volatile int * ptr_led)
{
	int i;
	for (i=0; i<MAX_NUM_LED+1; i++)
	{
	Led_OFF(ptr_led,i);
	}
}


void Led_ON_All (volatile int * ptr_led)
{
	int i;
	for (i=0; i<MAX_NUM_LED+1; i++)
	{
		Led_ON(ptr_led,i);
	}
}

void Led_ON_Some (volatile int * ptr_led, int n, int init_led)
{
	int i;

    // Check if the range is valid
    if (init_led < 0 || init_led > MAX_NUM_LED || n < 0 || (init_led + n - 1) > MAX_NUM_LED)
    {
        return;
    }

	for (i=0; i<n; i++)
	{
		Led_ON(ptr_led,i+init_led);
	}
}

void Led_OFF_Some (volatile int * ptr_led, int n, int init_led)
{
	int i;
	// Check if the range is valid
	if (init_led < 0 || init_led > MAX_NUM_LED || n < 0 || (init_led + n - 1) > MAX_NUM_LED)
	{
		return;
	}

	for (i=0; i<n; i++)
	{
		Led_OFF(ptr_led,i+init_led);
	}
}


void ledg_OFF_All (volatile int * ptr_led)
{
	int i;
	for (i=0; i<MAX_NUM_LED+1; i++)
	{
		Led_OFF(ptr_led,i);
	}
}




