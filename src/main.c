// CPSC 359 Project Part 2.
// Created by: Zeyad Omran (30096692) and Mohamed El Hefnawy (30093687).

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <time.h>
#include "main.h"

/* The frame buffer struct. */
struct fbs framebufferstruct;

/* The game's state. */
shared state;

/* main function */
int main(void) {

	/* initialize + get FBS */
	framebufferstruct = initFbInfo();

	/* Initialization */
	initState(&state);

	int activeButton = 1;
	/* Draws the start Screen */
	clearConsole();
	drawStartScreen(activeButton);
	srand(time(0));

	/* Program loop */
	while(true) {
		int button = getButtonPressed(); // Gets button pressed by SNES controller.
		if(state.showStartMenu) { // Checks if we are in the start menu.
			if((button == JD) && (activeButton == 1)) {
				activeButton = 2;
				clearConsole();
				drawStartScreen(activeButton);
			} else if((button == JU) && (activeButton == 2)) {
				activeButton = 1;
				clearConsole();
				drawStartScreen(activeButton);
			} else if((button == A) && (activeButton == 1)) { // Starts game.
				state.showStartMenu = false;
				activeButton = 1;
				clearConsole();
				refreshBoard(state);
			} else if((button == A) && (activeButton == 2)) { // Exits game.
				clearConsole();
				exit(0);
			}
		} else {
			if(state.showGameMenu) { // Checks if the game is paused.
				if((button == JD) && (activeButton == 1)) {
					activeButton = 2;
					clearConsole();
					drawPauseMenu(activeButton);
				} else if((button == JU) && (activeButton == 2)) {
					activeButton = 1;
					clearConsole();
					drawPauseMenu(activeButton);
				} else if((button == A) && (activeButton == 1)) { // Resumes game.
					state.showGameMenu = false;
					activeButton = 1;
					clearConsole();
					refreshBoard(state);
				} else if((button == A) && (activeButton == 2)) { // Quits game & displays start menu.
					state.showGameMenu = false;
					state.showStartMenu = true;
					drawStartScreen(1);
				}
			} else {
				if(button == STR) { // Pauses the game.
					state.showGameMenu = true;
					clearConsole();
					drawPauseMenu(1);
				}
			}
		}
		/* Delays the input to make sure that the SNES controller is not spamming. */
		delay(125);
	}
	munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
	return 0;
}

/**
 * Refreshes the game board.
 * 
 * @param state
 * 				The game's current state.
*/
void refreshBoard(shared state) {
	for(int i = 0; i < CELLSY; i++) {
		for(int j = 0; j < CELLSX; j++) {
			char cellType = state.gameMap.type[i][j];
			short int *imagePtr;
			int height;
			int width;
			if(cellType == CASTLE) {
				imagePtr = (short int *) GRNBORDERIMAGE.pixel_data;
				height = (int) GRNBORDERIMAGE.height;
				width = (int) GRNBORDERIMAGE.width;
			} else if(cellType == BLUBORDER) {
				imagePtr = (short int *) BLUBORDERIMAGE.pixel_data;
				height = (int) BLUBORDERIMAGE.height;
				width = (int) BLUBORDERIMAGE.width;
			} else if(cellType == REDBORDER) {
				imagePtr = (short int *) REDBORDERIMAGE.pixel_data;
				height = (int) REDBORDERIMAGE.height;
				width = (int) REDBORDERIMAGE.width;
			} else if(cellType == GRNBORDER) {
				imagePtr = (short int *) GRNBORDERIMAGE.pixel_data;
				height = (int) GRNBORDERIMAGE.height;
				width = (int) GRNBORDERIMAGE.width;
			} else if(cellType == BLKBORDER) {
				imagePtr = (short int *) BLKBORDERIMAGE.pixel_data;
				height = (int) BLKBORDERIMAGE.height;
				width = (int) BLKBORDERIMAGE.width;
			} else if(cellType == ZOMBIE1) {
				imagePtr = (short int *) ZOMBIE1IMAGE.pixel_data;
				height = (int) ZOMBIE1IMAGE.height;
				width = (int) ZOMBIE1IMAGE.width;
			} else if(cellType == ZOMBIE2) {
				imagePtr = (short int *) ZOMBIE2IMAGE.pixel_data;
				height = (int) ZOMBIE2IMAGE.height;
				width = (int) ZOMBIE2IMAGE.width;
			} else if(cellType == TILE) {
				imagePtr = (short int *) BLKBORDERIMAGE.pixel_data;
				height = (int) BLKBORDERIMAGE.height;
				width = (int) BLKBORDERIMAGE.width;
			} else if(cellType == SPACESHIP1) {
				imagePtr = (short int *) SPACESHIP1IMAGE.pixel_data;
				height = (int) SPACESHIP1IMAGE.height;
				width = (int) SPACESHIP1IMAGE.width;
			} else if(cellType == SPACESHIP2) {
				imagePtr = (short int *) SPACESHIP2IMAGE.pixel_data;
				height = (int) SPACESHIP2IMAGE.height;
				width = (int) SPACESHIP2IMAGE.width;
			} else if(cellType == SPACE) {
				imagePtr = (short int *) BLKBORDERIMAGE.pixel_data;
				height = (int) BLKBORDERIMAGE.height;
				width = (int) BLKBORDERIMAGE.width;
			} else if(cellType == LOG) {
				imagePtr = (short int *) LOGIMAGE.pixel_data;
				height = (int) LOGIMAGE.height;
				width = (int) LOGIMAGE.width;
			} else if(cellType == TURTLE) {
				imagePtr = (short int *) TURTLEIMAGE.pixel_data;
				height = (int) TURTLEIMAGE.height;
				width = (int) TURTLEIMAGE.width;
			} else if(cellType == WATER) {
				imagePtr = (short int *) WATERIMAGE.pixel_data;
				height = (int) WATERIMAGE.height;
				width = (int) WATERIMAGE.width;
			} else if(cellType == CAR1) {
				imagePtr = (short int *) CAR1IMAGE.pixel_data;
				height = (int) CAR1IMAGE.height;
				width = (int) CAR1IMAGE.width;
			} else if(cellType == CAR2) {
				imagePtr = (short int *) CAR2IMAGE.pixel_data;
				height = (int) CAR2IMAGE.height;
				width = (int) CAR2IMAGE.width;
			} else if(cellType == ROAD) {
				imagePtr = (short int *) BLKBORDERIMAGE.pixel_data;
				height = (int) BLKBORDERIMAGE.height;
				width = (int) BLKBORDERIMAGE.width;
			} else if(cellType == PLAYER) {
				imagePtr = (short int *) PLAYERIMAGE.pixel_data;
				height = (int) PLAYERIMAGE.height;
				width = (int) PLAYERIMAGE.width;
			} else {
				imagePtr = (short int *) BLKBORDERIMAGE.pixel_data;
				height = (int) BLKBORDERIMAGE.height;
				width = (int) BLKBORDERIMAGE.width;
			}
			int starty = (STARTY + (i * 40));
			int startx = (STARTX + (j * 40));
			// Draw the loaded image.
			drawImage(starty, startx, height, width, imagePtr);
		}
	}
}

/**
 *  Draws the Start Menu.
 * 
 * 	@param activeButton 
 * 				Which button is active in the start Menu.
 */
void drawStartScreen(int activeButton) {
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
	drawImage(STARTY, STARTX, height, width, startScreenPtr);
}

/**
 *  Draws the Pause Menu.
 * 
 * 	@param activeButton 
 * 				Which button is active in the Pause Menu.
 */
void drawPauseMenu(int activeButton) {
	// Declaring Variables
	short int *pauseMenuPtr;
	int height;
	int width;

	// Initializing Variables based on state
	if(activeButton == 1) {
		pauseMenuPtr = (short int *) PauseMenu1.pixel_data;
		height = (int) PauseMenu1.height;
		width = (int) PauseMenu1.width;
	} else {
		pauseMenuPtr = (short int *) PauseMenu2.pixel_data;
		height = (int) PauseMenu2.height;
		width = (int) PauseMenu2.width;
	}

	int starty = (STARTY + 120);
	int startx = (STARTX + 400);
	// Draw Image
	drawImage(starty, startx, height, width, pauseMenuPtr);
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
 */
void drawImage(int starty, int startx, int height, int width, short int *ptr) {
	/* initialize a pixel */
	Pixel pixel;
	// pixel = malloc(sizeof(Pixel));

	/* Printing the image. */
	int i = 0;
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			pixel.color = ptr[i];
			pixel.x = startx + x;
			pixel.y = starty + y;
			drawPixel(&pixel);
			i++;
		}
	}

	/* free pixel's allocated memory */
	// free(pixel);
	// pixel = NULL;
}

/**
 *  Draws a pixel.
 * 
 *  @param pixel 
 * 				A pointer to the pixel.	
 */
void drawPixel(Pixel *pixel) {
	long int location = (pixel->x + framebufferstruct.xOff) * (framebufferstruct.bits / 8) + (pixel->y + framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int *)(framebufferstruct.fptr + location)) = pixel->color;
}