/*
 * Motor control.c
 *
 * Created: 9/4/2024 11:55:02 PM
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
#include "PWM_register.h"

#include "LED_interface.h"
#include "SWITCH_interface.h"
#include "SSD_interface.h"
#include "LCD_interface.h"
#include "KPD_interface.h"
#include "LM35_interface.h"
#include "DCM_interface.h"
#include "SRVM_interface.h"

u8 x = KPD_NOT_PRESSED;
int main(void)
{	

	LCD_voidInit();
	KPD_voidInit();
	SRVM_voidInit();
    while (1) 
    {		
			//SRVM_voidOn(90);
		KPD_voidGetValue(&x);
		
		if (x != KPD_NOT_PRESSED)
		{
			if(x == '1')
			{
				SRVM_voidOn(180);
				LCD_voidClear();
				LCD_voidDisplayNumber(90);	
			}
			else if(x == '2')
			{
				SRVM_voidOn(90);
				LCD_voidClear();
				LCD_voidDisplayNumber(0);
			}
			else if(x == '3')
			{
				SRVM_voidOn(0);
				LCD_voidClear();
				LCD_voidDisplayString("-90");
			}
			else if(x == '4')
			{
				SRVM_voidOff();
				LCD_voidClear();
				LCD_voidDisplayString("OFF");
			}
		}
    }
}

