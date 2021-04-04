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

/* Dimentions */
#define WIDTH   1280
#define HEIGHT  760
#define STARTX  0
#define STARTY  0

/* SNES Controller Buttons */
#define B   1
#define Y   2
#define SEL 3
#define STR 4 
#define JU  5
#define JD  6
#define JL  7
#define JR  8
#define A   9
#define X   10
#define LFT 11
#define RGH 12

/* Prototypes */

int main(void);
void drawStartScreen(Pixel *pixel, int type);
void drawPauseMenu(Pixel *pixel, int activeButton);
void drawPixel(Pixel *pixel);

#endif