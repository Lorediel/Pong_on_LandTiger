/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../GLCD/GLCD.h"
#include "../myFunctions/myFunctions.h"
#include <stdlib.h>
#include <math.h>
#include <fenv.h>

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

unsigned short AD_current;   
unsigned short AD_last = 0xFF;     /* Last converted value               */

void ADC_IRQHandler(void) {
	
	//Soluzione per cancellare e ridisegnare tutta la paddle
	AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF); //Read Conversion Result
	// (240 - 10 - 50) / 5 = 36 -> 37 per la non idealità del potenziometro
	//4096 / 37 = 110
  if (abs(AD_current - AD_last)>110){
		drawPaddle((AD_last*37)/0xFFF, Black);
		drawPaddle((AD_current*37)/0xFFF, Green);
		
		AD_last = AD_current;
  }	
  	
	//Soluzione in teoria più fluide ma troppo lente sul simulatore 1px
	/*
	AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF); //Read Conversion Result             
  if (abs(AD_current - AD_last)>23){
		drawPaddle((AD_current*171)/0xFFF, Green);
		
		AD_last = AD_current;
  }	
	*/
	
	
}
