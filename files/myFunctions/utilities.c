#include "../GLCD/GLCD.h"
#include "myFunctions.h"
#include "../timer/timer.h"
#include <stdlib.h>
extern int timer2On;
extern int xspeed;
extern int yspeed;

//Disegno bordi
void drawBorders(void) {

	int j;
	for (j=0; j<5; j++){
		LCD_DrawLine(j, 0, j, 278, Red);
	}
	for (j=0; j<5; j++){
		LCD_DrawLine(0, j, 240, j, Red);
	}
	for (j=235; j<240; j++){
		LCD_DrawLine(j, 0, j, 278, Red);
	}
	
}

void reset(void){
	//reset le velocità ai valori iniziali
	xspeed = -4;
	yspeed = 4;
	//Cancella le scritte presenti
	GUI_Text(85, 160, (uint8_t *) "YOU LOSE", Black, Black);
	GUI_Text(50, 180, (uint8_t *) "PRESS INT0 TO RESET", Black, Black);
	//Ridisegna le scritte
	GUI_Text(50, 180, (uint8_t *) "PRESS KEY1 TO START", White, Black);
	//Disegna la pellet e mostra lo score
	drawPellet(232, 160);
	showScore();
	
}

void startGame(void){
	GUI_Text(50, 180, (uint8_t *) "PRESS KEY1 TO START", Black, Black);
	init_timer(1, 0x7A120);			//20 ms = 50 fps. Per yspeed = 4 => tempo per attraversare lo schermo è (320 - 42)/4 * 0.02 = 1.38 secondi.
	//init_timer(1, 0x98968);  //25 ms = 40 fps. 
	//init_timer(1, 0x5B8D8);  //15 ms
	//init_timer(1,0x0001e848), //5 ms
	//init_timer(1, 0x3D090); //10ms
	enable_timer(1); 
	//Riabilita key2
	NVIC_EnableIRQ(EINT2_IRQn);
}

void lose(void){
	//Disabilita il timer 1 per bloccare pallina e paddle
	disable_timer(1);
	//Cancella la pellet
	deletePellet();
	//Disabilita key2
	NVIC_DisableIRQ(EINT2_IRQn);
	GUI_Text(85, 160, (uint8_t *) "YOU LOSE", White, Black);
	GUI_Text(50, 180, (uint8_t *) "PRESS INT0 TO RESET", White, Black);
}

void pauseText(uint16_t color){
	GUI_Text(85, 160, (uint8_t *) "GAME PAUSED", color, Black);
}



// Function to swap two numbers
void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}
 
// Function to reverse `buffer[i…j]`
char* reverse(char *buffer, int i, int j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }
 
    return buffer;
}
 
// Iterative function to implement `itoa()` function in C
char* itoa(int value, char* buffer, int base)
{
		int n,i;
    // invalid input
    if (base < 2 || base > 32) {
        return buffer;
    }
 
    // consider the absolute value of the number
    n = abs(value);
 
    i = 0;
    while (n)
    {
        int r = n % base;
 
        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }
        else {
            buffer[i++] = 48 + r;
        }
 
        n = n / base;
    }
 
    // if the number is 0
    if (i == 0) {
        buffer[i++] = '0';
    }
 
    // If the base is 10 and the value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }
 
    buffer[i] = '\0'; // null terminate string
 
    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}


