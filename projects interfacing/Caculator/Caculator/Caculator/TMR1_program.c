/******************************************************************************
 *                                                                            *
 *************************  SWC     : TMR1_program    *************************
 *************************  Date    : 14/01/2024      *************************
 *************************  Author  : Kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "VECTOR_NUM.h"

/* MCAL */
#include "TMR1_interface.h"
#include "TMR1_config.h"
#include "TMR1_private.h"
#include "TMR1_register.h"


static void (*PRV_pFunCallBackOVF) (void)=NULL;
static void (*PRV_pFunCallBackCTCA)(void)=NULL;


void TMR1_voidInit(void)
{
#if TMR1_MODE == TMR1_NORMAL_MODE_0
	// Select Mode = Normal Mode 
	CLR_BIT(TCCR1A_REG,WGM10);
	CLR_BIT(TCCR1A_REG,WGM11);
	CLR_BIT(TCCR1B_REG,WGM12);
	CLR_BIT(TCCR1B_REG,WGM13);
	
	// Init Timer With Preload Value
	TCNT1_u16_REG = TMR1_PRELOAD_VALUE;
	
	// Enable OVF Interrupt
	SET_BIT(TIMSK_REG,TOIE1);
	
#elif TMR0_MODE == TMR0_CTC_MODE
	// Select Mode = CTC Mode (4)
	CLR_BIT(TCCR1A_REG,WGM10);
	CLR_BIT(TCCR1A_REG,WGM11);
	SET_BIT(TCCR1B_REG,WGM12);
	CLR_BIT(TCCR1B_REG,WGM13);
	
	// Init Timer With output compare Value
	OCR1A_u16_REG = TMR1_COMPARE_VALUE_A;
	
	// Enable OC Interrupt
	SET_BIT(TIMSK_REG,OCIE1A);

#endif	
}


void TMR1_voidStart(void)
{
#if TMR1_PRESCALER == TMR1_PRESCALER_1
    // Select Prescaler Value = 1
	SET_BIT(TCCR1B_REG,CS10);
	CLR_BIT(TCCR1B_REG,CS11);
	CLR_BIT(TCCR1B_REG,CS12);
#elif TMR1_PRESCALER == TMR1_PRESCALER_8
    // Select Prescaler Value = 8
	CLR_BIT(TCCR1B_REG,CS10);
	SET_BIT(TCCR1B_REG,CS11);
	CLR_BIT(TCCR1B_REG,CS12);
#elif TMR1_PRESCALER == TMR1_PRESCALER_64
	// Select Prescaler Value = 64
	SET_BIT(TCCR1B_REG,CS10);
	SET_BIT(TCCR1B_REG,CS11);
	CLR_BIT(TCCR1B_REG,CS12);
#elif TMR1_PRESCALER == TMR1_PRESCALER_256
	// Select Prescaler Value = 256
	CLR_BIT(TCCR1B_REG,CS10);
	CLR_BIT(TCCR1B_REG,CS11);
	SET_BIT(TCCR1B_REG,CS12);
#elif TMR1_PRESCALER == TMR1_PRESCALER_1024
	// Select Prescaler Value = 1024
	SET_BIT(TCCR1B_REG,CS10);
	CLR_BIT(TCCR1B_REG,CS11);
	SET_BIT(TCCR1B_REG,CS12);
#endif
}


void TMR1_voidStop(void)
{
	CLR_BIT(TCCR1B_REG,CS10);
	CLR_BIT(TCCR1B_REG,CS11);
	CLR_BIT(TCCR1B_REG,CS12);	
}


void TMR1_voidSetCallBack(void(*copy_pFunAction)(void), u8 copy_u8InterruptSource)
{
	if(copy_pFunAction!=NULL)
	{
		switch(copy_u8InterruptSource)
		{
			case TMR1_NORMAL_OVER_FLOW:
			PRV_pFunCallBackOVF = copy_pFunAction;
			break;
			
			case TMR1_CTC_COMPARE_MATCH_A:
			PRV_pFunCallBackCTCA = copy_pFunAction;
			break;
			
			default:
			// return error state
			break;
		}
	}
}


ISR(TIMER1_OVF)
{
	static u8 local_u8OVFCounter=0;
	local_u8OVFCounter++;
	
	if(TMR1_OVER_FLOW_COUNTER == local_u8OVFCounter)
	{
		// Init Timer With Preload Value
	    TCNT1_u16_REG = TMR1_PRELOAD_VALUE;
		
		// Clear Counter
	    local_u8OVFCounter=0;
		
		// Call Action
		if(PRV_pFunCallBackOVF!=NULL)
		{
			PRV_pFunCallBackOVF();
		}
	}
}


ISR(TIMER1_COMPA)
{
	static u16 local_u16CTCCounter=0;
	local_u16CTCCounter++;
	
	if(TMR1_CTC_COUNTER_A == local_u16CTCCounter)
	{
		// Clear Counter
		local_u16CTCCounter=0;
		
		// Call Action
		if(PRV_pFunCallBackCTCA!=NULL)
		{
			PRV_pFunCallBackCTCA();
		}
	}
}
