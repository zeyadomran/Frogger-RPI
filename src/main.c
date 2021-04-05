// CPSC 359 Project Part 2.
// Created by: Zeyad Omran (30096692) and Mohamed El Hefnawy (30093687).

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdbool.h>
#include "main.h"

/* The frame buffer struct. */
struct fbs framebufferstruct;
/* The game's state. */
shared state;

/* main function */
int main(void) {

	/* initialize + get FBS */
	framebufferstruct = initFbInfo();

	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));

	/* Initialization */
	initState(state);

	int activeButton = 1;
	/* Draws the start Screen */
	drawStartScreen(pixel, activeButton);
	
	/* Program loop */
	while(true) {
		int button = getButtonPressed(); // Gets button pressed by SNES controller.
		if(state.showStartMenu) { // Checks if we are in the start menu.
			if((button == JD) && (activeButton == 1)) {
				activeButton = 2;
				drawStartScreen(pixel, activeButton);
			} else if((button == JU) && (activeButton == 2)) {
				activeButton = 1;
				drawStartScreen(pixel, activeButton);
			} else if((button == A) && (activeButton == 1)) { // Starts game.
				state.showStartMenu = false;
				activeButton = 1;
				refreshBoard(pixel, state);
			} else if((button == A) && (activeButton == 2)) { // Exits game.
				exit(0);
			}
		} else {
			if(state.showGameMenu) { // Checks if the game is paused.
				if((button == JD) && (activeButton == 1)) {
					activeButton = 2;
					drawPauseMenu(pixel, activeButton);
				} else if((button == JU) && (activeButton == 2)) {
					activeButton = 1;
					drawPauseMenu(pixel, activeButton);
				} else if((button == A) && (activeButton == 1)) { // Resumes game.
					state.showGameMenu = false;
					activeButton = 1;
					refreshBoard(pixel, state);
				} else if((button == A) && (activeButton == 2)) { // Quits game & displays start menu.
					state.showGameMenu = false;
					state.showStartMenu = true;
				}
			} else {
				if(button == STR) { // Pauses the game.
					state.showGameMenu = true;
					drawPauseMenu(pixel, activeButton);
				}
			}
		}
		/* Delays the input to make sure that the SNES controller is not spamming. */
		delay(125);
	}

	/* free pixel's allocated memory */
	free(pixel);
	pixel = NULL;
	munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
	return 0;
}

void refreshBoard(Pixel *pixel, shared state) {
	for(int i = 0; i < CELLSY; i++) {
		for(int j = 0; j < CELLSX; j++) {
			char *cellType;
			short int *imagePtr;
			int height;
			int width;
			cellType = state.gameMap.type[i][j];
			if(strcmp(cellType, CASTLE) == 0) {
				imagePtr = (short int *) GRNBORDERIMAGE.pixel_data;
				height = (int) GRNBORDERIMAGE.height;
				width = (int) GRNBORDERIMAGE.width;
			} else if(strcmp(cellType, BLUBORDER) == 0) {
				imagePtr = (short int *) BLUBORDERIMAGE.pixel_data;
				height = (int) BLUBORDERIMAGE.height;
				width = (int) BLUBORDERIMAGE.width;
			} else if(strcmp(cellType, REDBORDER) == 0) {
				imagePtr = (short int *) REDBORDERIMAGE.pixel_data;
				height = (int) REDBORDERIMAGE.height;
				width = (int) REDBORDERIMAGE.width;
			} else if(strcmp(cellType, GRNBORDER) == 0) {
				imagePtr = (short int *) GRNBORDERIMAGE.pixel_data;
				height = (int) GRNBORDERIMAGE.height;
				width = (int) GRNBORDERIMAGE.width;
			} else if(strcmp(cellType, BLKBORDER) == 0) {
				imagePtr = (short int *) BLKBORDERIMAGE.pixel_data;
				height = (int) BLKBORDERIMAGE.height;
				width = (int) BLKBORDERIMAGE.width;
			} else if(strcmp(cellType, ZOMBIE1) == 0) {
				imagePtr = (short int *) ZOMBIE1IMAGE.pixel_data;
				height = (int) ZOMBIE1IMAGE.height;
				width = (int) ZOMBIE1IMAGE.width;
			} else if(strcmp(cellType, ZOMBIE2) == 0) {
				imagePtr = (short int *) ZOMBIE2IMAGE.pixel_data;
				height = (int) ZOMBIE2IMAGE.height;
				width = (int) ZOMBIE2IMAGE.width;
			} else if(strcmp(cellType, TILE) == 0) {
				imagePtr = (short int *) BLKBORDERIMAGE.pixel_data;
				height = (int) BLKBORDERIMAGE.height;
				width = (int) BLKBORDERIMAGE.width;
			}else if(strcmp(cellType, SPACESHIP1) == 0) {
				imagePtr = (short int *) SPACESHIP1IMAGE.pixel_data;
				height = (int) SPACESHIP1IMAGE.height;
				width = (int) SPACESHIP1IMAGE.width;
			} else if(strcmp(cellType, SPACESHIP2) == 0) {
				imagePtr = (short int *) SPACESHIP2IMAGE.pixel_data;
				height = (int) SPACESHIP2IMAGE.height;
				width = (int) SPACESHIP2IMAGE.width;
			} else if(strcmp(cellType, SPACE) == 0) {
				imagePtr = (short int *) BLKBORDERIMAGE.pixel_data;
				height = (int) BLKBORDERIMAGE.height;
				width = (int) BLKBORDERIMAGE.width;
			} else if(strcmp(cellType, LOG) == 0) {
				imagePtr = (short int *) LOGIMAGE.pixel_data;
				height = (int) LOGIMAGE.height;
				width = (int) LOGIMAGE.width;
			} else if(strcmp(cellType, TURTLE) == 0) {
				imagePtr = (short int *) TURTLEIMAGE.pixel_data;
				height = (int) TURTLEIMAGE.height;
				width = (int) TURTLEIMAGE.width;
			} else if(strcmp(cellType, WATER) == 0) {
				imagePtr = (short int *) WATERIMAGE.pixel_data;
				height = (int) WATERIMAGE.height;
				width = (int) WATERIMAGE.width;
			} else if(strcmp(cellType, CAR1) == 0) {
				imagePtr = (short int *) CAR1IMAGE.pixel_data;
				height = (int) CAR1IMAGE.height;
				width = (int) CAR1IMAGE.width;
			} else if(strcmp(cellType, CAR2) == 0) {
				imagePtr = (short int *) CAR2IMAGE.pixel_data;
				height = (int) CAR2IMAGE.height;
				width = (int) CAR2IMAGE.width;
			} else if(strcmp(cellType, ROAD) == 0) {
				imagePtr = (short int *) BLKBORDERIMAGE.pixel_data;
				height = (int) BLKBORDERIMAGE.height;
				width = (int) BLKBORDERIMAGE.width;
			} else if(strcmp(cellType, PLAYER) == 0) {
				imagePtr = (short int *) PLAYERIMAGE.pixel_data;
				height = (int) PLAYERIMAGE.height;
				width = (int) PLAYERIMAGE.width;
			} else if(strcmp(cellType, INFO) == 0) {
				imagePtr = (short int *) BLKBORDERIMAGE.pixel_data;
				height = (int) BLKBORDERIMAGE.height;
				width = (int) BLKBORDERIMAGE.width;
			}
			// Draw the loaded image.
			drawImage((STARTY * (i * CELLSY)), (STARTX * (j * CELLSX)), height, width, imagePtr, pixel);
		}
	}
}

/**
 *  Draws the Start Menu.
 *  @param pixel 
 * 				A pointer to a pixel.
 * 	@param activeButton 
 * 				Which button is active in the start Menu.
 */
void drawStartScreen(Pixel *pixel, int activeButton) {
	// Declaring Variables
	short int *startScreenPtr;
	int height;
	int width;
	
	// Initializing Variables based on state
	if(activeButton == 1) {
		startScreenPtr = (short int *) StartScreen1.pixel_data;
		height = (int) StartScreen1.height;
		width = (int) StartScreen1.width;
	} else {
		startScreenPtr = (short int *) StartScreen2.pixel_data;
		height = (int) StartScreen2.height;
		width = (int) StartScreen2.width;
	}

	// Draw Image
	drawImage(STARTY, STARTX, height, width, startScreenPtr, pixel);
}

/**
 *  Draws the Pause Menu.
 *  @param pixel 
 * 				A pointer to a pixel.
 * 	@param activeButton 
 * 				Which button is active in the Pause Menu.
 */
void drawPauseMenu(Pixel *pixel, int activeButton) {
	// Declaring Variables
	short int *pauseMenuPtr;
	int height;
	int width;

	// Initializing Variables based on state
	if(activeButton == 2) {
		pauseMenuPtr = (short int *) PauseMenu1.pixel_data;
		height = (int) PauseMenu1.height;
		width = (int) PauseMenu1.width;
	} else {
		pauseMenuPtr = (short int *) PauseMenu2.pixel_data;
		height = (int) PauseMenu2.height;
		width = (int) PauseMenu2.width;
	}
	
	// Draw Image
	drawImage((STARTY + 120), (STARTX + 400), height, width, pauseMenuPtr, pixel);
}


/**
 * Draws an image to the framebuffer.
 * 
 * @param starty
 * 				Where to start drawing on the Y axis.
 * @param startx
 * 				Where to start drawing on the X axis.
 * @param height
 * 				The height of the image.
 * @param width
 * 				The width of the image.
 * @param ptr
 * 				A pointer to the image.
 * @param pixel
 * 				A pointer to the pixel.	
 */
void drawImage(int starty, int startx, int height, int width, short int *ptr, Pixel *pixel) {
	int i = 0;
	for (int y = starty; y < height; y++) {
		for (int x = startx; x < width; x++) {	
			pixel->color = ptr[i]; 
			pixel->x = x;
			pixel->y = y;
			drawPixel(pixel);
			i++;
		}
	}
}

/**
 *  Draws a pixel.
 *  @param pixel 
 * 				A pointer to the pixel.	
 */
void drawPixel(Pixel *pixel) {
	long int location = (pixel->x +framebufferstruct.xOff) * (framebufferstruct.bits/8) + (pixel->y+framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int*)(framebufferstruct.fptr + location)) = pixel->color;
}