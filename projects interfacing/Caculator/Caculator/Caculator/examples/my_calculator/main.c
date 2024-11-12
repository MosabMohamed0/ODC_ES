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


u8 pressed='t';
u8 no='t';
u8 num1,num2,c=0,res;
BOOL flag =0;
u8 temp ;
void function_init();
int main(void)
{
	function_init();
    while (1) 
    {
 		KPD_voidGetValue(&pressed);
		if(pressed!=no)
		{	
			if(flag)
			{
				flag=0;
				LCD_voidClear();
			}
			else
			{	
				LCD_voidDisplayChar(pressed);
				if(pressed=='+')
				{
					res='+';
				}
				else if(pressed=='-')
				{
					res='-';
				}
				else if(pressed=='*')
				{
					res='*';
				}
				else if(pressed=='/')
				{
					res='/';
				}
				else if(pressed=='#')
				{
					c=0;
					LCD_voidClear();
				}
				else if(pressed =='=')
				{
					temp = pressed;
					if(res=='+')
					{
						LCD_voidDisplayNumber((num1-'0')+(num2-'0'));
					}
					else if(res=='-')
					{
						LCD_voidDisplayNumber((num1-'0')-(num2-'0'));
					}
					else if(res=='*')
					{
						LCD_voidDisplayNumber((num1-'0')*(num2-'0'));
					}
					else if(res=='/')
					{
						LCD_voidDisplayNumber((num1-'0')/(num2-'0'));
					}
					flag=1;
					c=0;
				}
				else
				{
					if(c==0)
					num1=pressed;
					else if(c==1)
					num2=pressed;
					c++;
				}	
			}
			pressed=no;
		}
    }
}

void function_init(){
	KPD_voidInit();
	LCD_voidInit();
}
