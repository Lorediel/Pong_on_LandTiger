#include "../GLCD/GLCD.h"
#include "myFunctions.h"

uint16_t leftPaddleCoord;

//La paddle ha lunghezza 50 px

void drawPaddle(uint16_t x, uint16_t color){
	// 5 px
	int j;
	//La paddle si muove con una granularità pari a 5.
	//Se x = 0 => inizio della paddle = 5
	//Se x = 1 => inizio paddle = 10 ...
	//Se x = 36 => inizio paddle = 180
	//Necessario perchè l'ultimo valore lo prende solo con il potenziometro a 0xFFF
	if (x==37){
		x=36;
	}
	x=(x+1)*5;
	
	for (j=0; j<10; j++){
		LCD_DrawLine(x, 278 + j, x+49, 278 + j, color);
	}
	
	leftPaddleCoord = x; 
	
	// Soluzione più fluida sulla board 
	/*
	for (j=0; j<10; j++){
		//Disegna un rettangolo nero a sinistra della paddle
		LCD_DrawLine(0, 278 + j, x-1, 278 + j, Black);
		//Disegna la paddle
		LCD_DrawLine(x, 278 + j, x+49, 278 + j, color);
		//Disegna un rettangolo nero a destra della paddle
		LCD_DrawLine(x+50, 278 + j, 239, 278 + j, color);
	}*/
}

