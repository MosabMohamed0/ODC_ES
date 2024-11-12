/*
 * Caculator.c
 *
 * Created: 9/4/2024 1:48:48 PM
 * Author : Mosab M. Zaafan
 */ 



// #include <avr/io.h>
// #include <stdio.h>
// #define F_CPU 16000000UL
// #include "STD_TYPES.h"
// #include "BIT_MATH.h"
// #include "DIO_interface.h"
// #include "DIO_register.h"
// #include "LED_interface.h"
// #include "SWITCH_interface.h"
// #include <util/delay.h>
// #include "SSD_interface.h"
// #include "SSD_config.h"
// #include "SSD_private.h"
// #include "LCD_interface.h"
// #include "LCD_config.h"
// #include "LCD_private.h"
// #include "KPD_interface.h"
// #include "KPD_config.h"

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


int main(void)
{
	u8 x = KPD_NOT_PRESSED;
	f32 num1 = 0;
	f32 num2 = 0;
	f32 result = 0;
	u8 op = 0;
	u8 is_num2_flag = 0;

	KPD_voidInit();
	LCD_voidInit();
	LCD_voidDisplayString("####  HELLO ####");
	_delay_ms(1000);
	LCD_voidClear();
	while (1)
	{
		KPD_voidGetValue(&x);
		
		if (x != KPD_NOT_PRESSED)
		{
			if (x >= '0' && x <= '9')
			{
				u8 one_digit = x - '0';
				LCD_voidDisplayNumber(one_digit);
				if (is_num2_flag)
				{
					num2 = num2 * 10 + one_digit;	
				}
				else
				{
					num1 = num1 * 10 + one_digit;
				}
			}
			else if (x == '+' || x == '-' || x == '*' || x == '/')
			{
				op = x;
				is_num2_flag = 1; 
				LCD_voidDisplayChar(x);
			}
			else if (x == '=')
			{
				switch (op)
				{
					case '+': result = num1 + num2; break;
					case '-': result = num1 - num2; break;
					case '*': result = num1 * num2; break;
					case '/': result = num1 / num2; break;
				}

				LCD_voidDisplayChar('=');
				LCD_voidDisplayNumber((u32)result); 
				num1 = result; 
				num2 = 0; 
				is_num2_flag = 0;
			}
			else if (x == '#')
			{
				LCD_voidClear();
				is_num2_flag = 0;
				op = 0;
				num1 = 0;
				num2 = 0;
				result = 0;
			}
			x = KPD_NOT_PRESSED;
		}
	}
}
