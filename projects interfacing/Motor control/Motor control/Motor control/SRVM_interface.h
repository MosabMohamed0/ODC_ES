/******************************************************************************
 *                                                                            *
 *************************  SWC     : SRVM_interface  *************************
 *************************  Date    : 14/01/2024      *************************
 *************************  Author  : kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/


#ifndef SRVM_INTERFACE_H_
#define SRVM_INTERFACE_H_


#define SRVM_DESIRED_FREQUENCY			50

                         /*************** APIS PROTO TYPES ***************/

void SRVM_voidInit(void);
void SRVM_voidOn  (u8 Copy_u8Angle);
void SRVM_voidOff (void);


#endif /* SRVM_INTERFACE_H_ */
