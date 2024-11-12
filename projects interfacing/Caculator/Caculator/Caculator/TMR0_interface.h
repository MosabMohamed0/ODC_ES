/******************************************************************************
 *                                                                            *
 *************************  SWC     : TMR0_interface  *************************
 *************************  Date    : 11/01/2024      *************************
 *************************  Author  : Kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/

#ifndef TMR0_INTERFACE_H_
#define TMR0_INTERFACE_H_


/* MACROS FOR TIMER INTERRUPT SOURCE */
#define TMR0_NORMAL_OVER_FLOW         1
#define TMR0_CTC_COMPARE_MATCH        2

                         /*************** APIS PROTOTYPES ***************/
void TMR0_voidInit       (void);
void TMR0_voidStart      (void);
void TMR0_voidStop       (void);
void TMR0_voidSetCallBack(void(*copy_pFunAction)(void), u8 copy_u8InterruptSource);


#endif /* TMR0_INTERFACE_H_ */
