/******************************************************************************
 *                                                                            *
 *************************  SWC     : TMR2_program    *************************
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
#include "TMR2_interface.h"
#include "TMR2_config.h"
#include "TMR2_private.h"
#include "TMR2_register.h"


static void (*PRV_pFunCallBackOVF)(void)=NULL;
static void (*PRV_pFunCallBackCTC)(void)=NULL;


void TMR2_voidInit(void)
{
#if TMR2_MODE == TMR2_NORMAL_MODE
	// Select Mode = Normal Mode 
	CLR_BIT(TCCR2_REG,WGM20);
	CLR_BIT(TCCR2_REG,WGM21);
	
	// Init Timer With Preload Value
	TCNT2_REG = TMR2_PRELOAD_VALUE;
	
	// Enable OVF Interrupt
	SET_BIT(TIMSK_REG,TOIE2);
	
#elif TMR2_MODE == TMR2_CTC_MODE
	// Select Mode = CTC Mode 
	CLR_BIT(TCCR2_REG,WGM20);
	SET_BIT(TCCR2_REG,WGM21);
	
	// Init Timer With output compare Value
	OCR2_REG = TMR2_COMPARE_VALUE;
	
	// Enable OC Interrupt
	SET_BIT(TIMSK_REG,OCIE2);

#endif	
}


void TMR2_voidStart(void)
{
#if TMR2_PRESCALER == TMR2_PRESCALER_1
    // Select Prescaler Value = 1
	SET_BIT(TCCR2_REG,CS20);
	CLR_BIT(TCCR2_REG,CS21);
	CLR_BIT(TCCR2_REG,CS22);
#elif TMR2_PRESCALER == TMR2_PRESCALER_8
    // Select Prescaler Value = 8
	CLR_BIT(TCCR2_REG,CS20);
	SET_BIT(TCCR2_REG,CS21);
	CLR_BIT(TCCR2_REG,CS22);
#elif TMR2_PRESCALER == TMR2_PRESCALER_32
	// Select Prescaler Value = 64
	SET_BIT(TCCR2_REG,CS20);
	SET_BIT(TCCR2_REG,CS21);
	CLR_BIT(TCCR2_REG,CS22);
#elif TMR2_PRESCALER == TMR2_PRESCALER_64
	// Select Prescaler Value = 64
	CLR_BIT(TCCR2_REG,CS20);
	CLR_BIT(TCCR2_REG,CS21);
	SET_BIT(TCCR2_REG,CS22);
#elif TMR2_PRESCALER == TMR2_PRESCALER_128
	// Select Prescaler Value = 64
	SET_BIT(TCCR2_REG,CS20);
	CLR_BIT(TCCR2_REG,CS21);
	SET_BIT(TCCR2_REG,CS22);
#elif TMR2_PRESCALER == TMR2_PRESCALER_256
	// Select Prescaler Value = 256
	CLR_BIT(TCCR2_REG,CS20);
	SET_BIT(TCCR2_REG,CS21);
	SET_BIT(TCCR2_REG,CS22);
#elif TMR2_PRESCALER == TMR2_PRESCALER_1024
	// Select Prescaler Value = 1024
	SET_BIT(TCCR2_REG,CS20);
	SET_BIT(TCCR2_REG,CS21);
	SET_BIT(TCCR2_REG,CS22);
#endif
}


void TMR2_voidStop(void)
{
	CLR_BIT(TCCR2_REG,CS20);
	CLR_BIT(TCCR2_REG,CS21);
	CLR_BIT(TCCR2_REG,CS22);	
}


void TMR2_voidSetCallBack(void(*copy_pFunAction)(void), u8 copy_u8InterruptSource)
{
	if(copy_pFunAction!=NULL)
	{
		switch(copy_u8InterruptSource)
		{
			case TMR2_NORMAL_OVER_FLOW:
			PRV_pFunCallBackOVF = copy_pFunAction;
			break;
			
			case TMR2_CTC_COMPARE_MATCH:
			PRV_pFunCallBackCTC = copy_pFunAction;
			break;
			
			default:
			// return error state
			break;
		}
	}
}


ISR(TIMER2_OVF)
{
	static u16 local_u16OVFCounter=0;
	local_u16OVFCounter++;
	
	if(TMR2_OVER_FLOW_COUNTER == local_u16OVFCounter)
	{
		// Init Timer With Preload Value
		TCNT2_REG = TMR2_PRELOAD_VALUE;
		
		// Clear Counter
		local_u16OVFCounter=0;
		
		// Call Action
		if(PRV_pFunCallBackOVF!=NULL)
		{
			PRV_pFunCallBackOVF();
		}
	}
}


ISR(TIMER2_COMP)
{
	static u16 local_u16CTCCounter=0;
	local_u16CTCCounter++;
	
	if(TMR2_CTC_COUNTER == local_u16CTCCounter)
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
