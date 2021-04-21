// CPSC 359 Project Part 2.
// Created by: Zeyad Omran (30096692) and Mohamed El Hefnawy (30093687).

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "main.h"

/* The frame buffer struct. */
struct fbs framebufferstruct;

/* The game's state. */
shared state;

/* Active button for menu */
int activeButton = 1;

/* Button pressed by controller */
int button = -1;

// GPIOPointer
unsigned int * gpioPtr; 

/* main function */
int main(void) {

	/* initialize + get FBS */
	framebufferstruct = initFbInfo();

	/* Initialization */
	initState(&state);

	// Initializing GPIO
	gpioPtr = getGPIOPtr();
	Init_GPIO(gpioPtr);

	/* Objects thread. */
	pthread_t objectThr;
	pthread_create(&objectThr, NULL, objectThread, NULL);

	/* draw Thread. */
	pthread_t dThr; 
	pthread_create(&dThr, NULL, drawThread, NULL);

	/* controller Thread. */
	pthread_t cThr; 
	pthread_create(&cThr, NULL, controllerThread, NULL);

	/* time Thread. */
	pthread_t timeThr; 
	pthread_create(&timeThr, NULL, timeThread, NULL);

	srand(time(0));

	/* Program loop */
	while(true) {
		if(state.showStartMenu) { // Checks if we are in the start menu.
			if((button == JD) && (activeButton == 1)) {
				activeButton = 2;
				button = -1;
			} else if((button == JU) && (activeButton == 2)) {
				activeButton = 1;
				button = -1;
			} else if((button == A) && (activeButton == 1)) { // Starts game.
				state.showStartMenu = false;
				activeButton = 1;
				button = -1;
			} else if((button == A) && (activeButton == 2)) { // Exits game.
				munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
				exit(0);
			}
		} else if(state.winFlag || state.loseFlag) {
			pthread_cancel(objectThr);
			printf("Moves Left: " + state.movesLeft); 
			printf("Lives Left: " + state.livesLeft); 
			printf("Time Left " + state.timeLeft);
			if(button != -1) {
				pthread_cancel(dThr);
				munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
				exit(0);
			}
		} else {
			if(state.showGameMenu) { // Checks if the game is paused.
				if((button == JD) && (activeButton == 1)) {
					activeButton = 2;
					button = -1;
				} else if((button == JU) && (activeButton == 2)) {
					activeButton = 1;
					button = -1;
				} else if((button == A) && (activeButton == 1)) { // Resumes game.
					state.showGameMenu = false;
					activeButton = 1;
					button = -1;
				} else if((button == A) && (activeButton == 2)) { // Quits game & displays start menu.
					state.showGameMenu = false;
					state.showStartMenu = true;
					button = -1;
				}
			} else {
				if(button == STR) { // Pauses the game.
					state.showGameMenu = true;
					button = -1;
				} else {
					if((button == JU) || (button == JD) || (button == JR) || (button == JL)) {
						movePlayer(&state, button);
						button = -1;
					}
				}
			}
		}
	}
	munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
	return 0;
}

/**
 * Refreshes the game board.
*/
void refreshBoard() {
	int counter = 0;
	for(int i = 0; i < CELLSY; i++) {
		for(int j = 0; j < CELLSX; j++) {
			char cellType = state.gameMap[i][j];
			short int *imagePtr;
			int height;
			int width;
			if(cellType == PLAYER) {
				imagePtr = (short int *) PLAYERIMAGE.pixel_data;
				height = (int) PLAYERIMAGE.height;
				width = (int) PLAYERIMAGE.width;
			} else if(cellType == CASTLE) {
				imagePtr = (short int *) GRNBORDERIMAGE.pixel_data;
				height = (int) GRNBORDERIMAGE.height;
				width = (int) GRNBORDERIMAGE.width;
			} else if(cellType == WINZONE) {
				imagePtr = (short int *) BLUBORDERIMAGE.pixel_data;
				height = (int) BLUBORDERIMAGE.height;
				width = (int) BLUBORDERIMAGE.width;
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
			} else if(cellType == INFO) {
				imagePtr = (short int *) BLKBORDERIMAGE.pixel_data;
				height = (int) BLKBORDERIMAGE.height;
				width = (int) BLKBORDERIMAGE.width;
			}
			int starty = (STARTY + (i * 40));
			int startx = (STARTX + (j * 40));
			// Draw the loaded image.
			drawImage(starty, startx, height, width, imagePtr);
			counter += 1;
		}
	}
}

/**
 *  Draws the Start Menu.
 */
void drawStartScreen() {
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
 */
void drawPauseMenu() {
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
 *  Draws the Win/Lose Banner.
 */
void drawWinLoseBanner() {
	// Declaring Variables
	short int *flag;
	int height;
	int width;

	// Initializing Variables based on state
	if(state.winFlag) {
		flag = (short int *) WinFlag.pixel_data;
		height = (int) WinFlag.height;
		width = (int) WinFlag.width;
	} else {
		flag = (short int *) LoseFlag.pixel_data;
		height = (int) LoseFlag.height;
		width = (int) LoseFlag.width;
	}

	int starty = (STARTY + 120);
	int startx = (STARTX + 400);
	// Draw Image
	drawImage(starty, startx, height, width, flag);
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

	/* Printing the image. */
	int i = 0;
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			pixel.color = ptr[i];
			pixel.x = startx + x;
			pixel.y = starty + y;
			stagePixel(&pixel);
			i++;
		}
	}
}

/**
 *  Stages a pixel.
 * 
 *  @param pixel 
 * 				A pointer to the pixel.	
 */
void stagePixel(Pixel *pixel) {
	long int location = (pixel->x + framebufferstruct.xOff) * (framebufferstruct.bits / 8) + (pixel->y + framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int *)(state.stage + location)) = pixel->color;
}

/**
 *  Draws to the framebuffer.
 */
void drawFB() {
	memcpy(framebufferstruct.fptr, state.stage, (1280 * 720 * 2));
}

// Thread stuff

/**
 * The function that will handle all object threads.
 */
void * objectThread() {
    while(true) {
        while(state.showStartMenu || state.showGameMenu) {}
		sleep(0.8);
		int counter = 0;
		for (int i = 0; i < CELLSY; i++) {
			for (int j = 0; j < CELLSX; j++) {
				int x = state.objs[counter].posX;
				int v = state.objs[counter].velocity;
				if (v != 0) {
					if((x + v) < CELLSX && (x + v) >= 0) {
						x = x + v;
					} else {
						if((x + v) >= CELLSX) x = 0;
						else x = CELLSX - 1;
					}
					updateCell(&state, state.objs[counter].type, state.objs[counter].posY, x, v, counter);
				} else {
					updateCell(&state, state.objs[counter].type, state.objs[counter].posY, x, v, counter);
				}
				counter += 1;
			}
		}
		int x = state.player.posX;
		int v = state.player.velocity;
		if(v != 0) {
			if((x + v) < CELLSX && (x + v) >= 0) {
				x = x + v;
			} else {
				if((x + v) >= CELLSX) x = 0;
				else x = CELLSX - 1;
			}
			updatePlayer(&state, PLAYER, state.player.posY, x, v);
		}
		checkCell(&state);
    }
}

/**
 * The function the will handle the draw thread. 
 */
void * drawThread() {
	while(true) {
		if(state.showStartMenu) { // Checks if we are in the start menu.
			drawStartScreen();
			drawFB();
		} else if(state.winFlag || state.loseFlag) {
			drawWinLoseBanner();
			drawFB();
		} else if(state.showGameMenu) {
			drawPauseMenu();
			drawFB();
		} else {
			refreshBoard();
			drawFB();
		}
	}
}

/**
 * The function the will handle the controller thread. 
 */
void * controllerThread() {
	while(true) {
		button = getButtonPressed(gpioPtr);
		sleep(0.25);
	}
}

/**
 * The function that will handle the time thread. 
 */
void * timeThread() {
	while(true) {
		while(state.showStartMenu || state.showGameMenu) {}
		int timeLeft = state.timeLeft;
		timeLeft -= 1;
		state.timeLeft = timeLeft;
		if(state.timeLeft <= 0) {
			state.loseFlag = true;
		}
		sleep(1);
	}
}