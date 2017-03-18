/*
 * func.c
 *
 *  Created on: 16 Mar 2017
 *      Author: Roosbeh Almasi
 */


#include "mcu.h"
#include "func.h"

void *ptr;


void CLK_init(void)
{
 /**************************************************************************************************
  *
  *  CLKs initialisation
  *                         System Core CLK is 120MHz
  * ***********************************************************************************************/

	SIM->SCGC4 |= 1UL<<10;                   //Enable the clk on UART0
	SIM->SCGC6 |= 1UL<<23;                   //Enable the clk on PIT timer
	SIM->SCGC5 |= (1UL<<10 | 1UL<<13);       //Enable the clk on PORT B and E
	SIM->SOPT5 &= ~(0xF);                    //Ensures the UART0 pins are the data source

}
/***************************************************************************************************
 *
 *        RGB LED initialisation
 *
 * ************************************************************************************************/

void LEDs_init(void)
{
	PORTB->PCR[22] |= 1UL<<8;                            //Select Pins as General Purpose IO
	PORTB->PCR[21] |= 1UL<<8;
	PORTE->PCR[26] |= 1UL<<8;

	PTB->PDDR |= (1UL<<21 | 1UL<<22);                    //Select pins as outputs
	PTE->PDDR |= 1UL<<26;

    PTB->PSOR |= (1UL<<21 | 1UL<<22);                    //Set the pin outpputs to 1, turn the LEDs OFF
    PTE->PSOR |= 1UL<<26;

}
/*******************************************************************************************************
 *
 *     PIT Timer initialisation
 *
 * ****************************************************************************************************/


void PIT_init(void)
{
	/* PIT is DownCounter */
	PIT->MCR &= ~(1UL<<1 | 1UL);                        //Enables the clk to PIT and PIT runs in debug mode
	PIT->CHANNEL[0].TCTRL &= ~(1UL | 1UL<<1 | 1UL<<2);  //Disable PIT, IRQ and not chain
	PIT->CHANNEL[0].LDVAL =0x55D4A80 ;                  //PIT value, 1.5s and resets
    PIT->CHANNEL[0].TCTRL |= 1UL;                       //PIT Enabled
  //PIT->CHANNEL[0].CVAL = PIT CurrentValue             //Could read the current value

}

/********************************************************************************************
 *
 *
 *   UART0 Function definition
 *
 * *****************************************************************************************/

void UART_init(void)
{
	PORTB->PCR[16] |= (1UL<<8 | 1UL<<9);       //Select pin for UART0 Rx
	PORTB->PCR[17] |= (1UL<<8 | 1UL<<9);       //Select pin for UART0 Tx

	UART_TxRx_Dis();
	UART0->C1 = 0;                    //Normal operation, No parity, (stopbit+8bit data+startbit)
	UART0->BDH = 0x03;
	UART0->BDL = 0x0D;                  // Baud rate = 9600 b/s
	UART0->C4  = 0x8;                   // BRFA value 01000 for 0.25 BRFD
	UART0->S2 &= ~1UL<<5;                // LSB first
	UART0->PFIFO = 0x88;                 //Tx and Rx FIFO enabled with depth 1 dataword
}

void UART_Tx_Dis(void)
{
    UART0->C2 &= ~(1UL<<3);
}
void UART_Tx_Ena(void)
{
	UART0->C2 |= 1UL<<3;
}
void UART_Rx_Dis(void)
{
	UART0->C2 &= ~(1UL<<2);
}
void UART_Rx_Ena(void)
{
	UART0->C2 |= 1UL<<2;
}
void UART_TxRx_Dis(void)
{
	UART0->C2 &= ~(1<<3 | 1<<2);
}


void UART_putchar(char ch)
{

	while(!(UART0_S1 & UART_S1_TDRE_MASK));
	     UART0_D =(uint8_t)ch;

}

void put(char *str)
{
	while(*str)
	{
      UART_putchar(*str++);

	}

}

uint8_t UART_getchar(void)
{
 	while(!(UART0_S1 & UART_S1_RDRF_MASK));
         return UART0_D;
}

/********************************************************************************************************
 *
 *             RGB LED drivers
 *
 * *****************************************************************************************************/



void redLED_ON(void)
{
   PTB->PSOR |= 1UL<<21;
   PTE->PSOR |= 1UL<<26;
   PTB->PCOR |= 1UL<<22;
}
void greenLED_ON(void)
{
   PTB->PSOR |= (1UL<<22 | 1UL<<21);
   PTE->PCOR |= 1UL<<26;
}
void blueLED_ON(void)
{
   PTB->PSOR |= 1UL<<22;
   PTE->PSOR |= 1UL<<26;
   PTB->PCOR |= 1UL<<21;
}
void LEDs_OFF(void)
{
   PTE->PSOR |= 1UL<<26;
   PTB->PSOR |= (1UL<<22 | 1UL<<21);
}
void LEDs_ON(void)
{
   PTE->PCOR |= 1UL<<26;
   PTB->PCOR |= (1UL<<22 | 1UL<<21);
}
void LEDs_Flashing(void)
{
  uint32_t val = PIT->CHANNEL[0].CVAL;

  if((val < _PIT_90_) && (val>= _PIT_60_)  )
  {
     redLED_ON();
  }
  else if((val < _PIT_60_) && (val >= _PIT_30_))
  {
    greenLED_ON();
  }
  else if((val < _PIT_30_) || (val == _PIT_90_))
  {
    blueLED_ON();
  }

}

void ProcessCMD(uint8_t *cmd)
{
	switch(*cmd)
	{
	  case 'r':
		  redLED_ON();
		  break;
	  case 'g':
		  greenLED_ON();
		  break;
	  case 'b':
		  blueLED_ON();
		  break;
	  case 'n':
		  LEDs_OFF();
		  break;
	  case 'a':
		  LEDs_ON();
		  break;
	  default:
		  LEDs_Flashing();
	      break;
	}

}


