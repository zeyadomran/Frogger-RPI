#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "framebuffer.h"
#include "../backend/SNESDRIVER/SNES_DRIVER.c"

/* Definitions */
typedef struct {
	int color;
	int x, y;
} Pixel;

struct fbs framebufferstruct;
void drawPixel(Pixel *pixel);

/* Definitions */
#define WIDTH 1280
#define HEIGHT 720

/* main function */
int main(){
	/* initialize + get FBS */
	framebufferstruct = initFbInfo();
	
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {	
				pixel->color = 0x61FF58; // Green
				pixel->x = x;
				pixel->y = y;
				drawPixel(pixel);
		}
	}

	/* free pixel's allocated memory */
	free(pixel);
	pixel = NULL;
	munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
	int button = -1;
	while(button == -1) {
		button = getButtonPressed();
		delay(125);
	}
	printf(button);
	return 0;
}

/* Draw a pixel */
void drawPixel(Pixel *pixel){
	long int location = (pixel->x +framebufferstruct.xOff) * (framebufferstruct.bits/8) + (pixel->y+framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int*)(framebufferstruct.fptr + location)) = pixel->color;
}

