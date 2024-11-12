/******************************************************************************
 *                                                                            *
 *************************  SWC     : TMR2_register   *************************
 *************************  Date    : 14/01/2024      *************************
 *************************  Author  : Kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/

#ifndef TMR2_REGISTER_H_
#define TMR2_REGISTER_H_


// Timer/Counter Control Register
#define TCCR2_REG			(*(volatile u8*)0x45)
#define CS20                0
#define CS21                1
#define CS22                2
#define WGM21               3
#define COM20               4
#define COM21               5
#define WGM20               6
#define FOC2                7

// Timer/Counter Register
#define TCNT2_REG           (*(volatile u8*)0x44)

// Output Compare Register
#define OCR2_REG            (*(volatile u8*)0x43)

// Timer/Counter Interrupt Mask Register
#define TIMSK_REG           (*(volatile u8*)0x59)
#define TOIE2               6
#define OCIE2               7

// Timer/Counter Interrupt Flag Register
#define TIFR_REG            (*(volatile u8*)0x58)
#define TOV2                6
#define OCF2                7


#endif /* TMR2_REGISTER_H_ */
