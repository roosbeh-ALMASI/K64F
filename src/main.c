/*******************************************************************************
File:     main.c

Developer : Roosbeh Almasi

******************************************************************************/

#include "mcu.h"
#include "func.h"
//#include "tiny_printf.h"

int main(void)
{

	CLK_init();
	UART_init();
	UART_Tx_Ena();
/*

    SIM->SCGC6 |= SIM_SCGC6_FTM0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
    PORTD->PCR[5] = PORT_PCR_MUX(4);

    NVIC_EnableIRQ(FTM0_IRQn);

    FTM0->SC |= 0x004f;
    FTM0->MOD = 60000;
    FTM0_C5SC |= 0x0028;
    FTM0_C5V = 500;
*/

    while (1)
    {

    	printf("roosbehAlmasi = %d \r\n", 1982);

    }

    return 0;
}


void FTM0_IRQHandler(void)
{
	unsigned long ChannelValue = FTM0_C5V;

	(void)FTM0_SC;
	FTM0_SC &= ~(0x0080);

	if(ChannelValue < 60000)
	{
		FTM0_C5V += 500;
	}else{
		    FTM0_C5V = 0;
	}
}
