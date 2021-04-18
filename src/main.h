#ifndef Main
#define Main

/* Includes */
#include "framebuffer.h"
#include "SNES_Driver.h"
#include "game.h"
#include "assets.h"

/* Pixel struct */
typedef struct {
	short int color;
	int x, y;
} Pixel;

/* Clears the screen. */
#define clearConsole() printf("\e[1;1H\e[2J")

/* Dimensions */
#define WIDTH 	1280
#define HEIGHT 	720
#define STARTX 	0
#define STARTY 	0

#define NANOSECONDMULTIPLIER  1000000  // 1 millisecond = 1,000,000 Nanoseconds


/* Prototypes */

int main(void);
void refreshBoard(shared state);
void drawStartScreen(int type);
void drawPauseMenu(int activeButton);
void drawWinLoseBanner();
void drawImage(int starty, int startx, int height, int width, short int *ptr);
void drawPixel(Pixel *pixel);
void * objectThread(void* oID);
void * playerThread();
void * drawThread();

#endif