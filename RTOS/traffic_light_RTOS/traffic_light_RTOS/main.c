/*
 * traffic_light_RTOS.c
 *
 * Created: 9/12/2024 9:47:41 AM
 * Author : Mosab M. Zaafan
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "VECTOR_NUM.h"
#include "RTOS_interface.h"
#include "DIO_interface.h"
#include "LED_interface.h"
#include "SSD_interface.h"

void Traffic_Light(void);

int main(void)
{
	LED_voidInit(DIO_PORTC, DIO_PIN0);
	LED_voidInit(DIO_PORTC, DIO_PIN1);
	LED_voidInit(DIO_PORTC, DIO_PIN2);
	SSD_voidInit();
	
	RTOS_createTask(0, 1,&Traffic_Light);
	RTOS_start();
	
	while (1)
	{
	}
}

void Traffic_Light(void)
{
		LED_voidOff(DIO_PORTC, DIO_PIN1, LED_FORWARD_CONNECTION); 
		LED_voidOff(DIO_PORTC, DIO_PIN2, LED_FORWARD_CONNECTION);
		LED_voidOn(DIO_PORTC, DIO_PIN0, LED_FORWARD_CONNECTION);  
		for(int i = 1 ; i<=60;i++)
		{
			SSD_voidDisplayMultiplexedNumber(i);
			_delay_ms(1000);
		}
		LED_voidOff(DIO_PORTC, DIO_PIN0, LED_FORWARD_CONNECTION); 
		LED_voidOff(DIO_PORTC, DIO_PIN2, LED_FORWARD_CONNECTION); 
		LED_voidOn(DIO_PORTC, DIO_PIN1, LED_FORWARD_CONNECTION); 
		for(int i = 1 ; i<=5;i++)
		{
			SSD_voidDisplayMultiplexedNumber(i);
			_delay_ms(1000);
		} 
		LED_voidOff(DIO_PORTC, DIO_PIN0, LED_FORWARD_CONNECTION); 
		LED_voidOff(DIO_PORTC, DIO_PIN1, LED_FORWARD_CONNECTION); 
		LED_voidOn(DIO_PORTC, DIO_PIN2, LED_FORWARD_CONNECTION);  
		for(int i = 1 ; i<=60;i++)
		{
			SSD_voidDisplayMultiplexedNumber(i);
			_delay_ms(1000);
		}  
}