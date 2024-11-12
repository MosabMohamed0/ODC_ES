/******************************************************************************
 *                                                                            *
 *************************  SWC     : TMR2_config     *************************
 *************************  Date    : 14/01/2024      *************************
 *************************  Author  : Kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/

#ifndef TMR2_CONFIG_H_
#define TMR2_CONFIG_H_


/* Options FOR TMR2 Mode:
1- TMR2_NORMAL_MODE
2- TMR2_CTC_MODE
*/
#define TMR2_MODE					TMR2_CTC_MODE

/* Options FOR PRESCALER:
1- TMR2_PRESCALER_1
2- TMR2_PRESCALER_8
3- TMR2_PRESCALER_32
4- TMR2_PRESCALER_64
5- TMR2_PRESCALER_128
6- TMR2_PRESCALER_256
7- TMR2_PRESCALER_1024
*/ 
#define TMR2_PRESCALER              TMR2_PRESCALER_64

#define TMR2_PRELOAD_VALUE          113
#define TMR2_OVER_FLOW_COUNTER      977

#define TMR2_COMPARE_VALUE          249
#define TMR2_CTC_COUNTER            1000


#endif /* TMR2_CONFIG_H_ */
