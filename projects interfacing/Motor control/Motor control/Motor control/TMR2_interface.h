/******************************************************************************
 *                                                                            *
 *************************  SWC     : TMR2_interface  *************************
 *************************  Date    : 14/01/2024      *************************
 *************************  Author  : Kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/

#ifndef TMR2_INTERFACE_H_
#define TMR2_INTERFACE_H_


/* MACROS FOR TIMER INTERRUPT SOURCE */
#define TMR2_NORMAL_OVER_FLOW         1
#define TMR2_CTC_COMPARE_MATCH        2

                /*************** APIS PROTOTYPES ***************/
void TMR2_voidInit       (void);
void TMR2_voidStart      (void);
void TMR2_voidStop       (void);
void TMR2_voidSetCallBack(void(*copy_pFunAction)(void), u8 copy_u8InterruptSource);


#endif /* TMR2_INTERFACE_H_ */
