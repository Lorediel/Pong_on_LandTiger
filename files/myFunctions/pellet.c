#include "../GLCD/GLCD.h"
#include "myFunctions.h"
#include "../timer/timer.h"

volatile int xspeed = -4;
volatile int yspeed = 4;
volatile int xCurrentPos;
volatile int yCurrentPos;
extern uint16_t leftPaddleCoord;  //x più a sinistra di paddle, definita in paddle.c

unsigned int lost;
extern int recordScoreLength;

void drawPellet(uint16_t xCenter, uint16_t yCenter)
{
	int j;
	//Se supera il bordo destro riposizionala in modo che lo tocchi
	if (xCenter > 232){
		xCenter  = 232;
	}
	//Bordo sinistro
	if (xCenter < 7){
		xCenter  = 7;
	}
	//Bordo in alto
	if (yCenter < 7){
		yCenter = 7;
	}
	//Bordo in basso (dove c'è la paddle)
	if (yCenter > 275){
		yCenter = 275;
	}
	//Disegna facendo 5 linee
	for (j=0; j<5; j++){
		LCD_DrawLine(xCenter-2, (yCenter-2)+j, (xCenter+2), (yCenter-2)+j, Green);
	}
	//Setta la posizione
	xCurrentPos = xCenter;
	yCurrentPos = yCenter;
}

//Cancella la pellet disegnandola di nero
void deletePellet(void){
	int j;
	for (j=0; j<5; j++){
		LCD_DrawLine(xCurrentPos-2, (yCurrentPos-2)+j, (xCurrentPos+2), (yCurrentPos-2)+j, Black);
	}
}

void checkBorderHits(){
	//Se si trova sul bordo destro o sinistro
	if (xCurrentPos == 232 || xCurrentPos == 7){
		xspeed = -xspeed;
		//Riproduci il suono del bordo
		setTimer2Interval(1417);
		enable_timer(2);
	}
	//Se si trova sul bordo in alto
	if (yCurrentPos == 7){
		yspeed = -yspeed;
		setTimer2Interval(1417);
		enable_timer(2);
	}
	
}


//Controlla se la pellet ha colpito la paddle
int hitsPaddle(){
	//Se la x della pallet si trova nella zona della paddle, return 1, altrimenti 0
	if (xCurrentPos >= leftPaddleCoord - 2 && xCurrentPos <= leftPaddleCoord + 49 + 2){
		return 1;
	}
	else
	{
		return 0;
	}
}

void managePaddleHit(void){
	//Riproduci il suono
	setTimer2Interval(1062);
	enable_timer(2);
	//Se colpisce il lato sinistro della paddle la xspeed aumenta di 1 se colpisce da destra (xspeed negativa)
	//Diminuisce di 1 se colpisce da sinistra (xspeed positiva)
	//La velocità a sua volta diminuisce e aumenta rispettivamente, questo per mantenere più o meno una velocità uguale
	//Se la velocità è già al minimo (-6), l'angolo è uguale a quello di incidenza
	if (xCurrentPos >= (leftPaddleCoord -2) && xCurrentPos <= (leftPaddleCoord + 15)){
		if (xspeed > 2){
			xspeed = xspeed - 1;
			yspeed = -(yspeed + 1);
		}
		else if (xspeed <= -2 && xspeed > -6){
			xspeed = xspeed - 1;
			yspeed = -(yspeed - 1);
		}
		else{
			yspeed = -yspeed;
		}
	}
	//Se colpisce la parte centrale della paddle l'angolo è uguale a quello di incidenza
	else if (xCurrentPos >= (leftPaddleCoord +16) && xCurrentPos <= (leftPaddleCoord + 33)){
			yspeed = -yspeed;
	}
	//Se colpisce la parte di destra aumenta di 1 se colpisce da sinistra (xspeed positiva)
	//Diminuisce di 1 se colpisce da destra
	//Se la velocità è già al massimo (6) l'angoo è quello di incidenza
	else{
		if (xspeed < -2){
			xspeed = xspeed + 1;
			yspeed = -(yspeed + 1);
		}
		else if (xspeed < 6 && xspeed >= 2){
			xspeed = xspeed + 1;
			yspeed = -(yspeed - 1);
		}
		else{
			yspeed = -yspeed;
		}
		
	}
	hideScore();
	addScore();
	showScore();
	
	
}
/*
262Hz	k=2120		c4
294Hz	k=1890		
330Hz	k=1684		
349Hz	k=1592		
392Hz	k=1417		
440Hz	k=1263		
494Hz	k=1125		
523Hz	k=1062		c5

*/




void move(void){
	deletePellet();
	//Controlla se la pellet si trova sopra allo score
	if (yCurrentPos <= 177 && yCurrentPos >= 158 && xCurrentPos <= (20 + (scoreLength - 1) * 8) && xCurrentPos >= 7){
		showScore();
	}
	//Controlla se la pellet si trova sul record, in quel caso lo cancella e ridisegna
	else if (yCurrentPos <= 28 && yCurrentPos >= 7 && xCurrentPos >= 230-(8*recordScoreLength)-3){
		showRecord();
	}
	drawPellet(xCurrentPos + xspeed, yCurrentPos + yspeed);
	

	checkBorderHits();
	//Se la pellet si trova giù controlla se colpisce la paddle, se la colpisce gestisci l'hit, altrimenti lose
	if (yCurrentPos == 275){
		if (hitsPaddle() == 1){
			managePaddleHit();
		}
		else{
			lost = 1;
			lose();
		}
	}
	
}


