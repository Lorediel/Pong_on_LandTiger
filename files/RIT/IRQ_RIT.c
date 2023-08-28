/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../myFunctions/myFunctions.h"
#include "../timer/timer.h"
#include "../GLCD/GLCD.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


extern int pressedKey;				//Definita in IRQ_button per sapere quale bottone si è premuto
extern unsigned int lost;			//Definita in pellet e settata a 1 se si perde

void RIT_IRQHandler (void)
{				
	//Variabile flag per iniziare la partita
	static unsigned char startable = 1;
	//Variabile flag per mettere vedere se la partita è in pausa
	static unsigned char paused = 0;
	static int down = 0;
	if (pressedKey == 0){
		down++;
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){
			reset_RIT();
			switch(down){
				case 1:
					if (lost == 1){
						reset();
						lost = 0;
						startable = 1;
					}
					break;
				default:
					break;
			}
		}
		else {	// button released 
			down=0;	
			disable_RIT();
			reset_RIT();
			NVIC_EnableIRQ(EINT0_IRQn);
			NVIC_EnableIRQ(EINT1_IRQn);
			NVIC_EnableIRQ(EINT2_IRQn);
			LPC_PINCON->PINSEL4    |= (1 << 20);     // External interrupt 0 pin selection
		}
	}
	else if(pressedKey == 1){
		down++;
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
			reset_RIT();
			switch(down){
				case 1:
					if (startable == 1){
						startGame();
						startable = 0;
					}
					break;
				default:
					break;
			}
		}
		else {	// button released 
			down=0;
			disable_RIT();
			reset_RIT();
			NVIC_EnableIRQ(EINT0_IRQn);
			NVIC_EnableIRQ(EINT1_IRQn);
			NVIC_EnableIRQ(EINT2_IRQn);
			
			LPC_PINCON->PINSEL4    |= (1 << 22);     // External interrupt 0 pin selection 
		}
		
	}
	else if (pressedKey == 2){
		down++;
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
			reset_RIT();
			switch(down){
				case 1:
					if(paused == 0){
						disable_timer(1);
						disable_timer(2);
						paused = 1;
						pauseText(White);		//Definita in utilities per scrivere "GAME PAUSED"
					}
					else
					{
						enable_timer(1);
						paused = 0;
						pauseText(Black);
					}
					break;
				default:
					break;
			}
		}
		else {	// button released
			down=0;			
			disable_RIT();
			reset_RIT();
			NVIC_EnableIRQ(EINT0_IRQn);
			NVIC_EnableIRQ(EINT1_IRQn);
			NVIC_EnableIRQ(EINT2_IRQn);	
			LPC_PINCON->PINSEL4    |= (1 << 24);     // External interrupt 0 pin selection 
		}
		
	}
	
	LPC_RIT->RICTRL |= 0x1;	// clear interrupt flag 
	
  return;
		
	}
	

/******************************************************************************
**                            End Of File
******************************************************************************/
