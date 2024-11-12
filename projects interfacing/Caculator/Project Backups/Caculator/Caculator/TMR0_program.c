/******************************************************************************
 *                                                                            *
 *************************  SWC     : TMR0_program    *************************
 *************************  Date    : 11/01/2024      *************************
 *************************  Author  : Kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "VECTOR_NUM.h"

/* MCAL */
#include "TMR0_interface.h"
#include "TMR0_config.h"
#include "TMR0_private.h"
#include "TMR0_register.h"


static void (*PRV_pFunCallBackOVF)(void)=NULL;
static void (*PRV_pFunCallBackCTC)(void)=NULL;


void TMR0_voidInit(void)
{
#if TMR0_MODE == TMR0_NORMAL_MODE
	// Select Mode = Normal Mode 
	CLR_BIT(TCCR0_REG,WGM00);
	CLR_BIT(TCCR0_REG,WGM01);
	
	// Init Timer With Preload Value
	TCNT0_REG = TMR0_PRELOAD_VALUE;
	
	// Enable OVF Interrupt
	SET_BIT(TIMSK_REG,TOIE0);
	
#elif TMR0_MODE == TMR0_CTC_MODE
	// Select Mode = CTC Mode 
	CLR_BIT(TCCR0_REG,WGM00);
	SET_BIT(TCCR0_REG,WGM01);
	
	// Init Timer With output compare Value
	OCR0_REG = TMR0_COMPARE_VALUE;
	
	// Enable OC Interrupt
	SET_BIT(TIMSK_REG,OCIE0);

#endif	
}


void TMR0_voidStart(void)
{
#if TMR0_PRESCALER == TMR0_PRESCALER_1
    // Select Prescaler Value = 1
	SET_BIT(TCCR0_REG,CS00);
	CLR_BIT(TCCR0_REG,CS01);
	CLR_BIT(TCCR0_REG,CS02);
#elif TMR0_PRESCALER == TMR0_PRESCALER_8
    // Select Prescaler Value = 8
	CLR_BIT(TCCR0_REG,CS00);
	SET_BIT(TCCR0_REG,CS01);
	CLR_BIT(TCCR0_REG,CS02);
#elif TMR0_PRESCALER == TMR0_PRESCALER_64
	// Select Prescaler Value = 64
	SET_BIT(TCCR0_REG,CS00);
	SET_BIT(TCCR0_REG,CS01);
	CLR_BIT(TCCR0_REG,CS02);
#elif TMR0_PRESCALER == TMR0_PRESCALER_256
	// Select Prescaler Value = 256
	CLR_BIT(TCCR0_REG,CS00);
	CLR_BIT(TCCR0_REG,CS01);
	SET_BIT(TCCR0_REG,CS02);
#elif TMR0_PRESCALER == TMR0_PRESCALER_1024
	// Select Prescaler Value = 1024
	SET_BIT(TCCR0_REG,CS00);
	CLR_BIT(TCCR0_REG,CS01);
	SET_BIT(TCCR0_REG,CS02);
#endif
}


void TMR0_voidStop(void)
{
	CLR_BIT(TCCR0_REG,CS00);
	CLR_BIT(TCCR0_REG,CS01);
	CLR_BIT(TCCR0_REG,CS02);	
}


void TMR0_voidSetCallBack(void(*copy_pFunAction)(void), u8 copy_u8InterruptSource)
{
	if(copy_pFunAction!=NULL)
	{
		switch(copy_u8InterruptSource)
		{
			case TMR0_NORMAL_OVER_FLOW:
			PRV_pFunCallBackOVF = copy_pFunAction;
			break;
			
			case TMR0_CTC_COMPARE_MATCH:
			PRV_pFunCallBackCTC = copy_pFunAction;
			break;
			
			default:
			// return error state
			break;
		}
	}
}


ISR(TIMER0_OVF)
{
	static u16 local_u16OVFCounter=0;
	local_u16OVFCounter++;
	
	if(TMR0_OVER_FLOW_COUNTER == local_u16OVFCounter)
	{
		// Init Timer With Preload Value
	    TCNT0_REG = TMR0_PRELOAD_VALUE;
		
		// Clear Counter
		local_u16OVFCounter=0;
		
		// Call Action
		if(PRV_pFunCallBackOVF!=NULL)
		{
			PRV_pFunCallBackOVF();
		}
	}
}


ISR(TIMER0_COMP)
{
	static u16 local_u16CTCCounter=0;
	local_u16CTCCounter++;
	
	if(TMR0_CTC_COUNTER == local_u16CTCCounter)
	{
		// Clear Counter
		local_u16CTCCounter=0;
		
		// Call Action
		if(PRV_pFunCallBackCTC!=NULL)
		{
			PRV_pFunCallBackCTC();
		}
	}
}
