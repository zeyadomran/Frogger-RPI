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

/* Dimensions */
#define WIDTH 	1280
#define HEIGHT 	720
#define STARTX 	0
#define STARTY 	0

/* Prototypes */

int main(void);
void refreshBoard();
void drawStartScreen();
void drawPauseMenu();
void drawWinLoseBanner();
void drawImage(int starty, int startx, int height, int width, short int *ptr);
void stagePixel(Pixel *pixel);
void drawFB();
void * objectThread();
void * controllerThread();
void * drawThread();
void * timeThread();

#endif