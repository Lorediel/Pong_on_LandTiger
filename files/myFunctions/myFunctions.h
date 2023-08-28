//utilities functions
extern void drawBorders(void);
extern void reset(void);
extern void startGame(void);
void lose(void);
void pauseText(uint16_t color);
void showRecord(void);
void hideRecord(void);
char* itoa(int value, char* buffer, int base);


//Pellet functions
extern void deletePellet(void);
extern void move(void);
extern void drawPellet(uint16_t xCenter, uint16_t yCenter);

//Padddle functions
extern void drawPaddle(uint16_t x, uint16_t color);
extern uint16_t leftPaddleCoord;

//Score functions
extern void addScore(void);
extern void showScore(void);
extern void hideScore(void);
extern void resetScore(void);
extern int scoreLength;
extern int score;
extern int record;
