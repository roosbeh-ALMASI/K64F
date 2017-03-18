/******************************************************************************************
 * func.h
 *
 *  Created on: 16 Mar 2017
 *  Author: Roosbeh Almasi
 *****************************************************************************************/

#ifndef FUNC_H_
#define FUNC_H_


#include <stdlib.h>


#define _PIT_90_    0x55D4A80
#define _PIT_60_    0x3938700
#define _PIT_30_    0x1C9C380


void CLK_init(void);
void LEDs_init(void);
void PIT_init(void);
void UART_init(void);
void redLED_ON(void);
void greenLED_ON(void);
void blueLED_ON(void);
void LEDs_OFF(void);
void LEDs_ON(void);
void ProcessCMD(uint8_t *cmd);
void LEDs_Flashing(void);
void UART_Tx_Dis(void);
void UART_Tx_Ena(void);
void UART_Rx_Dis(void);
void UART_Rx_Ena(void);
void UART_TxRx_Dis(void);
void put(char *str);
uint8_t UART_getchar(void);
void UART_putchar(char ch);


#endif /* FUNC_H_ */
