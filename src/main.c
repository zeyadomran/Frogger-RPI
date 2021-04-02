#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdbool.h>
#include "framebuffer.h"
#include "SNES_Driver.h"
#include "game.h"
#include "assets.h"

/* Definitions */
typedef struct {
	short int color;
	int x, y;
} Pixel;

struct fbs framebufferstruct;
struct gameState state;
void drawPixel(Pixel *pixel);
void loadIMG(unsigned int height, unsigned int width, short int* ptr, Pixel *pixel, int yStart, int xStart);

/* Definitions */
#define WIDTH 1260
#define HEIGHT 700
// each cell is approx 35x35

/* main function */
int main(){
	/* initialize + get FBS */
	framebufferstruct = initFbInfo();
	
	/* Initialize Game */
	initializeState();
	state = getState(); // Get game state
	
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {	
			pixel->color = 0x000000; // Black
			pixel->x = x;
			pixel->y = y;
			drawPixel(pixel);
		}
	}

	for(int i = 0; i < CELLSY; i++) {
		for(int j = 0; j < CELLSX; j++) {
			if(state.gameMap[i][j] == BLACKBG);
			if(state.gameMap[i][j] == CREATORS) {
				short int *creatorPtr=(short int *) creators_banner.pixel_data;
				loadIMG(creators_banner.height, creators_banner.width, creatorPtr, pixel, i, j);
			}
			if(state.gameMap[i][j] == TITLE) {
				short int *titlePtr=(short int *) title_banner.pixel_data;
				loadIMG(title_banner.height, title_banner.width, titlePtr, pixel, i, j);
			}
			if(state.gameMap[i][j] == STARTGAME) {
				short int *startPtr=(short int *) startButton_inactive.pixel_data;
				loadIMG(startButton_inactive.height, startButton_inactive.width, startPtr, pixel, i, j);
			}
			if(state.gameMap[i][j] == QUITGAME) {
				short int *quitPtr=(short int *) quitButton_inactive.pixel_data;
				loadIMG(quitButton_inactive.height, quitButton_inactive.width, quitPtr, pixel, i, j);
			}
			//printf(" %d", state.gameMap[i][j]);
		}
		//printf("\n");
	}

	/* free pixel's allocated memory */
	free(pixel);
	pixel = NULL;
	munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
	return 0;
}

/* Draw a pixel */
void drawPixel(Pixel *pixel){
	long int location = (pixel->x +framebufferstruct.xOff) * (framebufferstruct.bits/8) + (pixel->y+framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int*)(framebufferstruct.fptr + location)) = pixel->color;
}

/**
 * Takes a char image and display's it
 */
void loadIMG(unsigned int height, unsigned int width, short int* ptr, Pixel *pixel, int yStart, int xStart) {
	int i=0;
	for (int y = yStart * 35; y < height; y++) {
		for (int x = xStart * 35; x < width; x++) { 
			pixel->color = ptr[i]; 
			pixel->x = x;
			pixel->y = y;
			drawPixel(pixel);
			i++;
		}
	}
}

/*
	int button = -1;
	while(button == -1) {
		button = getButtonPressed();
		delay(125);
	}
	printf(button);



*/