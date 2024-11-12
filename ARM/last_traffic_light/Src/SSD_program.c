/******************************************************************************
 *                                                                            *
 *************************  SWC     : SSD_program     *************************
 *************************  Date    : 25/02/2024      *************************
 *************************  Author  : Kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/


/*#define F_CPU 16000000UL
#include <util/delay.h>*/

#include <stdint.h>
/* UTILES_LIB */
#include "STM32F303xx.h"
#include "ERROR_TYPE.h"
#include "BIT_MATH.h"

/* MCAL */
#include "RCC_interface.h"
#include "GPIO_interface.h"

/* HAL */
#include "SSD_interface.h"
#include "SSD_config.h"
#include "SSD_private.h"

static uint8_t PRV_u8Numbers[10]= {SSD_ZERO, SSD_ONE, SSD_TWO, SSD_THREE, SSD_FOUR, SSD_FIVE, SSD_SEX, SSD_SEVEN, SSD_EIGHT, SSD_NINE};

void SSD_voidInit(void)
{
		RCC_voidSetClockStatus(RCC_CLK_HSI, RCC_CLK_ON);
		RCC_voidSetSystemClock(RCC_CLK_HSI);
		RCC_voidEnable_AHB_clock(RCC_AHB_IOPAEN);
		GPIO_pinConfig_t A = {.portId = GPIO_PORTC,.pinId = GPIO_PIN10,.pinMode = GPIO_OUTPUT,.pinOutputType = GPIO_PUSH_PULL};
		GPIO_pinConfig_t B = {.portId = GPIO_PORTC,.pinId = GPIO_PIN12,.pinMode = GPIO_OUTPUT,.pinOutputType = GPIO_PUSH_PULL};
		GPIO_pinConfig_t C = {.portId = GPIO_PORTF,.pinId = GPIO_PIN6,.pinMode = GPIO_OUTPUT,.pinOutputType = GPIO_PUSH_PULL};
		GPIO_pinConfig_t D = {.portId = GPIO_PORTF,.pinId = GPIO_PIN7,.pinMode = GPIO_OUTPUT,.pinOutputType = GPIO_PUSH_PULL};
		GPIO_pinConfig_t E = {.portId = GPIO_PORTA,.pinId = GPIO_PIN13,.pinMode = GPIO_OUTPUT,.pinOutputType = GPIO_PUSH_PULL};
		GPIO_pinConfig_t F = {.portId = GPIO_PORTA,.pinId = GPIO_PIN14,.pinMode = GPIO_OUTPUT,.pinOutputType = GPIO_PUSH_PULL};
		GPIO_pinConfig_t G = {.portId = GPIO_PORTA,.pinId = GPIO_PIN15,.pinMode = GPIO_OUTPUT,.pinOutputType = GPIO_PUSH_PULL};
		GPIO_pinConfig_t EN1 = {.portId = GPIO_PORTC,.pinId = GPIO_PIN2,.pinMode = GPIO_OUTPUT,.pinOutputType = GPIO_PUSH_PULL};
		//GPIO_pinConfig_t EN2 = {.portId = GPIO_PORTC,.pinId = GPIO_PIN3,.pinMode = GPIO_OUTPUT,.pinOutputType = GPIO_PUSH_PULL};
		GPIO_u8InitPin(&A);
		GPIO_u8InitPin(&B);
		GPIO_u8InitPin(&C);
		GPIO_u8InitPin(&D);
		GPIO_u8InitPin(&E);
		GPIO_u8InitPin(&F);
		GPIO_u8InitPin(&G);
		GPIO_u8InitPin(&EN1);
		//GPIO_u8InitPin(&EN2);
}


void SSD_voidDisplayNumber(uint8_t copy_u8DesiredNumber, uint8_t copy_u8Id)
{
	if(copy_u8DesiredNumber<=9)
	{
		switch(copy_u8Id)
		{
		    case SSD_ONE:
#if SSD_TYPE == SSD_COM_CATHODE
			PRV_voidWriteGroupOfPins(PRV_u8Numbers[copy_u8DesiredNumber]);
			GPIO_u8SetPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, GPIO_PIN_LOW);

#elif SSD_TYPE == SSD_COM_ANNODE
			PRV_voidWriteGroupOfPins(~PRV_u8Numbers[copy_u8DesiredNumber]);
			GPIO_u8SetPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, GPIO_PIN_HIGH);
#endif
			break;

		    case SSD_TWO:
#if SSD_TYPE == SSD_COM_CATHODE
			PRV_voidWriteGroupOfPins(PRV_u8Numbers[copy_u8DesiredNumber]);
			GPIO_u8SetPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, GPIO_PIN_LOW);

#elif SSD_TYPE == SSD_COM_ANNODE
			PRV_voidWriteGroupOfPins(~PRV_u8Numbers[copy_u8DesiredNumber]);
			GPIO_u8SetPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, GPIO_PIN_HIGH);
#endif
			break;
		}
	}
	else
	{
		// return Error state
	}
}


/*void SSD_voidDisplayMultiplexedNumber(u8 copy_u8DesiredNumber)
{
	if(copy_u8DesiredNumber<=99)
	{
		u8 local_u8Ones = copy_u8DesiredNumber%10;
		u8 local_u8Tens = copy_u8DesiredNumber/10;

#if SSD_TYPE == SSD_COM_CATHODE
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, DIO_PIN_HIGH);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, DIO_PIN_HIGH);
		DIO_voidSetPortValue(SSD_DATA_PORT, PRV_u8Numbers[local_u8Tens]);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, DIO_PIN_LOW);
		_delay_ms(10);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, DIO_PIN_HIGH);

		DIO_voidSetPortValue(SSD_DATA_PORT, PRV_u8Numbers[local_u8Ones]);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, DIO_PIN_LOW);
		_delay_ms(10);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, DIO_PIN_HIGH);

#elif SSD_TYPE == SSD_COM_ANNODE
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, DIO_PIN_LOW);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, DIO_PIN_LOW);
		DIO_voidSetPortValue(SSD_DATA_PORT, ~PRV_u8Numbers[local_u8Tens]);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, DIO_PIN_HIGH);
		_delay_ms(10);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, DIO_PIN_LOW);

		DIO_voidSetPortValue(SSD_DATA_PORT, ~PRV_u8Numbers[local_u8Ones]);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, DIO_PIN_HIGH);
		_delay_ms(10);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, DIO_PIN_LOW);
#endif
	}
	else
	{
		// return Error state
	}
}*/


static void PRV_voidWriteGroupOfPins(uint8_t copy_u8Value)
{
	if(0 == GET_BIT(copy_u8Value,0))
	{
		GPIO_u8SetPinValue(SSD_A_PORT, SSD_A_PIN, GPIO_PIN_LOW);
	}
	else
	{
		GPIO_u8SetPinValue(SSD_A_PORT, SSD_A_PIN, GPIO_PIN_HIGH);
	}
	if(0 == GET_BIT(copy_u8Value,1))
	{
		GPIO_u8SetPinValue(SSD_B_PORT, SSD_B_PIN, GPIO_PIN_LOW);
	}
	else
	{
		GPIO_u8SetPinValue(SSD_B_PORT, SSD_B_PIN, GPIO_PIN_HIGH);
	}
	if(0 == GET_BIT(copy_u8Value,2))
	{
		GPIO_u8SetPinValue(SSD_C_PORT, SSD_C_PIN, GPIO_PIN_LOW);
	}
	else
	{
		GPIO_u8SetPinValue(SSD_C_PORT, SSD_C_PIN, GPIO_PIN_HIGH);
	}
	if(0 == GET_BIT(copy_u8Value,3))
	{
		GPIO_u8SetPinValue(SSD_D_PORT, SSD_D_PIN, GPIO_PIN_LOW);
	}
	else
	{
		GPIO_u8SetPinValue(SSD_D_PORT, SSD_D_PIN, GPIO_PIN_HIGH);
	}
	if(0 == GET_BIT(copy_u8Value,4))
	{
		GPIO_u8SetPinValue(SSD_E_PORT, SSD_E_PIN, GPIO_PIN_LOW);
	}
	else
	{
		GPIO_u8SetPinValue(SSD_E_PORT, SSD_E_PIN, GPIO_PIN_HIGH);
	}
	if(0 == GET_BIT(copy_u8Value,5))
	{
		GPIO_u8SetPinValue(SSD_F_PORT, SSD_F_PIN, GPIO_PIN_LOW);
	}
	else
	{
		GPIO_u8SetPinValue(SSD_F_PORT, SSD_F_PIN, GPIO_PIN_HIGH);
	}
	if(0 == GET_BIT(copy_u8Value,6))
	{
		GPIO_u8SetPinValue(SSD_G_PORT, SSD_G_PIN, GPIO_PIN_LOW);
	}
	else
	{
		GPIO_u8SetPinValue(SSD_G_PORT, SSD_G_PIN, GPIO_PIN_HIGH);
	}
}

