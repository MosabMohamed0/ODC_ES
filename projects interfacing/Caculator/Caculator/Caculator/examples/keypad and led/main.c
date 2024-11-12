/*
 * Caculator.c
 *
 * Created: 9/4/2024 1:48:48 PM
 * Author : Mosab M. Zaafan
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "VECTOR_NUM.h"

#include "DIO_interface.h"
#include "GI_interface.h"
#include "ADC_interface.h"
#include "TMR0_interface.h"
#include "TMR1_interface.h"
#include "TMR2_interface.h"
#include "PWM_interface.h"

#include "LED_interface.h"
#include "SWITCH_interface.h"
#include "SSD_interface.h"
#include "LCD_interface.h"
#include "KPD_interface.h"
#include "LM35_interface.h"
#include "DCM_interface.h"
#include "SRVM_interface.h"


u8 x=0;
void function_init();
int main(void)
{
	function_init();
    while (1) 
    {
		KPD_voidGetValue(&x);
		if(x=='8')
		{
			LED_voidOn(DIO_PORTA,DIO_PIN2,LED_FORWARD_CONNECTION);
		}
		if(x=='2')
		{
			LED_voidOff(DIO_PORTA,DIO_PIN2,LED_FORWARD_CONNECTION);	
		}
    }
}

void function_init(){
	KPD_voidInit();
	LED_voidInit(DIO_PORTA,DIO_PIN2);
}
