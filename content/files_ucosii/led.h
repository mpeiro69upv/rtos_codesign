/*
 * led.h
 *
 *  Created on: 7 de dic. de 2023
 *      Author: mpeir
 */

#ifndef INC_LED_H_
#define INC_LED_H_

int Led_ON (volatile int * ptr_led, int i);
int Led_OFF (volatile int * ptr_led, int i);
int Toggle_Led (volatile int * ptr_led, int i);
void Led_OFF_All (volatile int * ptr_led);
void Led_ON_All (volatile int * ptr_led);
void Led_ON_Some (volatile int * ptr_led, int n, int init_led);
void Led_OFF_Some (volatile int * ptr_led, int n, int init_led);



#endif /* INC_LED_H_ */
