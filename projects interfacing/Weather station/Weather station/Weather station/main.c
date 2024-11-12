/*
 * Weather station.c
 *
 * Created: 9/4/2024 8:18:26 PM
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

u8 temp = 0;
int main(void)
{
	//ADC_voidInit(ADC_REFERENCE_AREF);
 	LM35_voidInit();
 	LCD_voidInit();
	DCM_voidInit(DCM_MOTOR_A);
	while (1)
	{
		LM35_voidGetTemperature(&temp);
		LCD_voidDisplayString("temp = ");
		LCD_voidDisplayNumber(temp);
 		if(temp<20)
 		{
 			DCM_voidOff(DCM_MOTOR_A);
 		}
 		else
 		{
 			DCM_voidOn(DCM_MOTOR_A,DCM_CLOCK_WISE);
 			if(temp<=25)
 			{
 				DCM_voidControlSpeed(DCM_MOTOR_A,DCM_CLOCK_WISE,50);
 			}
 			else if(temp<=30)
 			{
 				DCM_voidControlSpeed(DCM_MOTOR_A,DCM_CLOCK_WISE,70);
 			}
 			else if(temp<=35)
 			{
 				DCM_voidControlSpeed(DCM_MOTOR_A,DCM_CLOCK_WISE,90);
 			}
 			else if(temp<=40)
 			{
 				DCM_voidControlSpeed(DCM_MOTOR_A,DCM_CLOCK_WISE,100);
 			}
 			else
 			{
 				DCM_voidControlSpeed(DCM_MOTOR_A,DCM_CLOCK_WISE,100);
 			}	
		}
		_delay_ms(1000);
		LCD_voidClear();
	}
}











































