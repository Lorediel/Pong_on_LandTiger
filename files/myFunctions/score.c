#include "../GLCD/GLCD.h"
#include "myFunctions.h"
#include <math.h>
#include <stdio.h>

int score = 0;
int record = 100;
int scoreLength = 1;
int recordScoreLength = 3;

void addScore(void){
	if (score < 100){
		score = score + 5;
	}
	else{
		score = score + 10;
	}
	if (score > record){
		hideRecord();
		record = score;
		//Lunghezza del record
		recordScoreLength = (int)((ceil(log10(record)+0.001))*sizeof(char));
		showRecord();
	}
	//Calcola il numero di cifre dello score, utile per la scrittura quando la pellet passa sopra lo score.
	//log10 approssimato all'intero superiore più vicino
	scoreLength = (int)((ceil(log10(score)+0.001))*sizeof(char));
	
}



void showScore(void){
	char buffer[20];
	GUI_Text(10, 160, (uint8_t *) itoa(score, buffer, 10), White, Black);
}

void hideScore(void){
	char buffer[20];
	GUI_Text(10, 160, (uint8_t *) itoa(score, buffer, 10), Black, Black);
}

//230-3 x recordLength
//230 per lasciare un margine di 4 px dal bordo rosso di destra
void showRecord(void){
	char buffer[20];
	//Mostra il record inn modo appropriato
	GUI_Text(230-(8*recordScoreLength) , 10,(uint8_t *) itoa(record, buffer, 10), White, Black);
}

void hideRecord(void){
	char buffer[20];
	GUI_Text(230-(8*recordScoreLength), 10, (uint8_t *) itoa(record, buffer, 10), Black, Black);
}
