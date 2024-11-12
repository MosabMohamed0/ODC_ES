/******************************************************************************
 *                                                                            *
 *************************  SWC     : TMR0_config     *************************
 *************************  Date    : 11/01/2024      *************************
 *************************  Author  : Kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/

#ifndef TMR0_CONFIG_H_
#define TMR0_CONFIG_H_


/* Options FOR TMR0 Mode:
1- TMR0_NORMAL_MODE
2- TMR0_CTC_MODE
*/
#define TMR0_MODE					TMR0_NORMAL_MODE

/* Options FOR PRESCALER:
1- TMR0_PRESCALER_1
2- TMR0_PRESCALER_8
3- TMR0_PRESCALER_64
4- TMR0_PRESCALER_256
5- TMR0_PRESCALER_1024
*/ 
#define TMR0_PRESCALER              TMR0_PRESCALER_64

#define TMR0_PRELOAD_VALUE          113
#define TMR0_OVER_FLOW_COUNTER      977

#define TMR0_COMPARE_VALUE          249
#define TMR0_CTC_COUNTER            1000


#endif /* TMR0_CONFIG_H_ */
