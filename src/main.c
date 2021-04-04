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
				} else if((button == A) && (activeButton == 2)) { // Quits game & displays start menu.
					state.showGameMenu = false;
					state.showStartMenu = true;
				}
			} else {
				if(button == STR) { // Pauses the game.
					state.showGameMenu = true;
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
	
	// Initatializing Variables based on state
	if(activeButton == 1) {
		startScreenPtr = (int *) StartScreen1.pixel_data;
		height = (int) StartScreen1.height;
		width = (int) StartScreen1.width;
	} else {
		startScreenPtr = (int *) StartScreen2.pixel_data;
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

	// Initatializing Variables based on state
	if(activeButton == 2) {
		pauseMenuPtr = (int *) PauseMenu1.pixel_data;
		height = (int) PauseMenu1.height;
		width = (int) PauseMenu1.width;
	} else {
		pauseMenuPtr = (int *) PauseMenu2.pixel_data;
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
	long int location = (pixel->x +framebufferstruct.xOff) * (framebufferstruct.bits/8) 
						+ (pixel->y+framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int*)(framebufferstruct.fptr + location)) = pixel->color;
}