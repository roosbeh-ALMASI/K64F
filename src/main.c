/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 7.1.1   2017-03-10

The MIT License (MIT)
Copyright (c) 2009-2017 Atollic AB

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

#include "mcu.h"

int main(void)
{


    SIM->SCGC5 |= 1UL<<10 | 1UL<<13 | 1UL;  // enable clk on port B & E & LPTMR


    MCG->C2 &= ~1UL;                       // ensure! Select the slow internal 32KHz CLK to MCGIRCLK
    MCG->C1 |= 1UL<<1;                     // ensure! Enable the MCGIRCLK

    PORTB->PCR[22] |= 1UL << 8;
    PORTE->PCR[26] |= 1UL<<8;
    PTB->PDDR |= 1UL<<22;
    PTE->PDDR |= 1UL<<26;
    PTB->PSOR |= 1UL<<22;
    PTE->PSOR |= 1UL<<26;

/*
    SysTick->CTRL &= ~(1UL);
    SysTick->LOAD = 0xFFFFFF;
    SysTick->VAL = 0;
    SysTick->CTRL |=    (1UL<<2 | 1UL);

*/

    LPTMR0->CSR = 0;                //Disable the timer first
    LPTMR0->CMR = 0;
    LPTMR0->PSR = 0;

    LPTMR0->CSR = (1UL | 1UL<< 2);



    /* TODO - Add your application code here */
    while (1)
    {
/*
    	if((SysTick->CTRL & 1UL<<16) != 0 )
    	  {
    		PTB->PTOR |= 1UL<<22;
    	  }
*/

    	LPTMR0->CNR = 1;
    	if(LPTMR0->CNR  == 65535)
    	  {

    		PTE->PTOR |=1UL<<26;


    	  }


    }

    return 0;
}
