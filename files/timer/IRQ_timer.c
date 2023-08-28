/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../myFunctions/myFunctions.h"
#include "../adc/adc.h"
#include <stdio.h>

uint16_t SinTable[45] =                                      
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};

void TIMER1_IRQHandler (void)
{
	/* ADC management */
	ADC_start_conversion();
	move();
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}


void TIMER2_IRQHandler (void)
{
	static int ticks=0;	
	static char sin = 0;
	LPC_DAC->DACR = SinTable[ticks]<<6;
	ticks++;
	if(ticks==45){
		ticks=0;
		sin++;
		//riproduci per 2 sinusoidi
		if (sin == 2){
			sin=0;
			disable_timer(2);
			reset_timer(2);
		}
	}
	
	LPC_TIM2->IR = 1;			
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
