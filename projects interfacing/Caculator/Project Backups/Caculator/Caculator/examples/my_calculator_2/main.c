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
	u16 x = KPD_NOT_PRESSED;
	f32 first_operand = 0, second_operand = 0, result = 0;
	u8 operator = 0;
	u8 is_second_operand = 0;

	KPD_voidInit();
	LCD_voidInit();

	while (1)
	{
		KPD_voidGetValue(&x);
		
		if (x != KPD_NOT_PRESSED)
		{
			if (x >= '0' && x <= '9')
			{
				// Convert ASCII digit to integer
				u8 digit = x - '0';
				LCD_voidDisplayNumber(digit);

				if (!is_second_operand)
				{
					first_operand = first_operand * 10 + digit;
				}
				else
				{
					second_operand = second_operand * 10 + digit;
				}
			}
			else if (x == '+' || x == '-' || x == '*' || x == '/')
			{
				operator = x;
				is_second_operand = 1; // Switch to entering the second operand
				LCD_voidDisplayChar(x);
			}
			else if (x == '=')
			{
				switch (operator)
				{
					case '+': result = first_operand + second_operand; break;
					case '-': result = first_operand - second_operand; break;
					case '*': result = first_operand * second_operand; break;
					case '/':
					if (second_operand != 0)
					result = first_operand / second_operand;
					else
					LCD_voidDisplayString("Error");
					break;
				}

				LCD_voidDisplayChar('=');
				LCD_voidDisplayNumber((u32)result); // Display result as integer
				first_operand = result; // Store the result as the first operand for potential further operations
				second_operand = 0; // Reset second operand
				is_second_operand = 0; // Reset flag to indicate first operand input
			}
			else if (x == '#')
			{
				// Clear everything
				LCD_voidClear();
				first_operand = 0;
				second_operand = 0;
				result = 0;
				is_second_operand = 0;
				operator = 0;
			}

			_delay_ms(200); // Debounce delay
			x = KPD_NOT_PRESSED;
		}
	}
}
