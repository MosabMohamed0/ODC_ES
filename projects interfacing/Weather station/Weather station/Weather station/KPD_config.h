/*
 *
 * @file KPD_config.h
 * @author Kareem Hussein
 * @brief configuration header file contain configuraron macros for KPD
 * @date 23/08/2024      
 * @version 1.0
 *
 */

#ifndef HAL_KPD_INC_KPD_CONFIG_H_
#define HAL_KPD_INC_KPD_CONFIG_H_

                        /* MACROS FOR KPD ROWS/COLS PORTS & PINS CONFIGURATION */
		 
// Input   
#define KPD_ROW0_PORT			DIO_PORTC
#define KPD_ROW0_PIN 			DIO_PIN3

#define KPD_ROW1_PORT			DIO_PORTC
#define KPD_ROW1_PIN 			DIO_PIN4

#define KPD_ROW2_PORT			DIO_PORTC
#define KPD_ROW2_PIN 			DIO_PIN5

#define KPD_ROW3_PORT			DIO_PORTC
#define KPD_ROW3_PIN 			DIO_PIN6


//Output
#define KPD_COL0_PORT			DIO_PORTB
#define KPD_COL0_PIN 			DIO_PIN4
			
#define KPD_COL1_PORT			DIO_PORTB
#define KPD_COL1_PIN 			DIO_PIN5
			
#define KPD_COL2_PORT			DIO_PORTB
#define KPD_COL2_PIN 			DIO_PIN6
			
#define KPD_COL3_PORT			DIO_PORTB
#define KPD_COL3_PIN 			DIO_PIN7


#define KPD_KEYS			    {{'1','2','3','A'},\
                                 {'4','5','6','B'},\
								 {'7','8','9','C'},\
								 {'*','0','#','D'}}


#endif /* HAL_KPD_INC_KPD_CONFIG_H_ */
