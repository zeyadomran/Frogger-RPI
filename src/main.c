/* CPSC 359 Project Part 2. */
/* Created by: Zeyad Omran (30096692) and Mohamed El Hefnawy (30093687). */

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

/* GPIOPointer */
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

	/* Draw Thread. */
	pthread_t dThr; 
	pthread_create(&dThr, NULL, drawThread, NULL);

	/* Controller Thread. */
	pthread_t cThr; 
	pthread_create(&cThr, NULL, controllerThread, NULL);

	/* Time Thread. */
	pthread_t timeThr; 
	pthread_create(&timeThr, NULL, timeThread, NULL);

	/* Program loop */
	while(!state.gameOver) {}

	/* Cancelling active threads */
	pthread_cancel(objectThr);
	pthread_cancel(dThr);
	pthread_cancel(timeThr);
	pthread_cancel(cThr);

	/* Freeing Frame Buffer */
	munmap(framebufferstruct.fptr, framebufferstruct.screenSize);

	return 0;
}

/**
 * Refreshes the game board.
*/
void refreshBoard() {
	int startYLoop;
	int endYLoop;
	if(state.scene == 1) {
		startYLoop = 5;
		endYLoop = CELLSY;
	} else {
		startYLoop = 0;
		endYLoop = 16;
	}
	int counter = 0;
	for(int i = startYLoop; i < endYLoop; i++) {
		for(int j = 0; j < CELLSX; j++) {
			char cellType = state.gameMap[i][j];
			short int *imagePtr;
			switch(cellType) {
				case PLAYER:
					imagePtr = (short int *) PLAYERIMAGE.pixel_data;
					break;
				case CASTLE:
					imagePtr = (short int *) CASTLEIMAGE.pixel_data;
					break;
				case WINZONE:
					imagePtr = (short int *) TILEIMAGE.pixel_data;
					break;
				case BLUBORDER:
					imagePtr = (short int *) BLUBORDERIMAGE.pixel_data;
					break;
				case REDBORDER:
					imagePtr = (short int *) REDBORDERIMAGE.pixel_data;
					break;
				case GRNBORDER:
					imagePtr = (short int *) GRNBORDERIMAGE.pixel_data;
					break;
				case BLKBORDER:
					imagePtr = (short int *) BLKBORDERIMAGE.pixel_data;
					break;
				case ZOMBIE1:
					imagePtr = (short int *) ZOMBIE1IMAGE.pixel_data;
					break;
				case ZOMBIE2:
					imagePtr = (short int *) ZOMBIE2IMAGE.pixel_data;
					break;
				case TILE:
					imagePtr = (short int *) TILEIMAGE.pixel_data;
					break;
				case PURBORDER:
					imagePtr = (short int *) LevelBorder.pixel_data;
					break;
				case SPACESHIP1:
					imagePtr = (short int *) SPACESHIP1IMAGE.pixel_data;
					break;
				case SPACESHIP2:
					imagePtr = (short int *) SPACESHIP2IMAGE.pixel_data;
					break;
				case SPACE:
					imagePtr = (short int *) BLKBORDERIMAGE.pixel_data;
					break;
				case LOG:
					imagePtr = (short int *) LOGIMAGE.pixel_data;
					break;
				case TURTLE:
					imagePtr = (short int *) TURTLEIMAGE.pixel_data;
					break;
				case WATER:
					imagePtr = (short int *) WATERIMAGE.pixel_data;
					break;
				case CAR1:
					imagePtr = (short int *) CAR1IMAGE.pixel_data;
					break;
				case CAR2:
					imagePtr = (short int *) CAR2IMAGE.pixel_data;
					break;
				case ROAD:
					imagePtr = (short int *) BLKBORDERIMAGE.pixel_data;
					break;
				case VALUEPACK1:
					imagePtr = (short int *) GIFT1IMAGE.pixel_data;
					break;
				case VALUEPACK2:
					imagePtr = (short int *) GIFT3IMAGE.pixel_data;
					break;
				case VALUEPACK3:
					imagePtr = (short int *) GIFT4IMAGE.pixel_data;
					break;
				case VALUEPACK4:
					imagePtr = (short int *) COIN.pixel_data;
					break;
				case VALUEPACK5:
					imagePtr = (short int *) Heart.pixel_data;
					break;
				default:
					imagePtr = (short int *) BLKBORDERIMAGE.pixel_data;
			}
			/* Calculating Image Position */
			int starty;
			int startx= (STARTX + (j * 40));

			if(state.scene == 1) {
				starty = (STARTY + ((i - 5) * 40));
			} else {
				starty = (STARTY + (i * 40));
			}

			// Draw the loaded image.
			drawImage(starty, startx, 40, 40, imagePtr);
			counter++;
		}
	}
}

/**
 *  Draws the Start Menu.
 */
void drawStartScreen() {
	// Declaring Variables
	short int *startScreenPtr;

	// Initializing Variables based on state
	if(activeButton == 1) {
		startScreenPtr = (short int *) StartScreen1.pixel_data;
	} else {
		startScreenPtr = (short int *) StartScreen2.pixel_data;
	}

	// Draw Image
	drawImage(STARTY, STARTX, 720, 1280, startScreenPtr);
}

/**
 *  Draws the Pause Menu.
 */
void drawPauseMenu() {
	// Declaring Variables
	short int *pauseMenuPtr;

	// Initializing Variables based on state
	if(activeButton == 1) {
		pauseMenuPtr = (short int *) PAUSEMENU1.pixel_data;
	} else {
		pauseMenuPtr = (short int *) PAUSEMENU2.pixel_data;
	}

	int starty = (STARTY + 120);
	int startx = (STARTX + 400);
	// Draw Image
	drawImage(starty, startx, 480, 480, pauseMenuPtr);
}

/**
 *  Draws the Win/Lose Banner.
 */
void drawWinLoseBanner() {
	// Declaring Variables
	short int *flag;

	// Initializing Variables based on state
	if(state.winFlag) {
		flag = (short int *) WinFlag.pixel_data;
	} else {
		flag = (short int *) LoseFlag.pixel_data;
	}

	int starty = (STARTY + 120);
	int startx = (STARTX + 400);
	// Draw Image
	drawImage(starty, startx, 480, 480, flag);
}

/**
 * Gets the pointer to a digit's picture.
 * 
 * @param num
 * 			The digit you want.
 * @return The digit's image pointer. 
 */
short int * getNumPicture(char num) {
	switch(num) {
		case '0':
			return (short int *) ZERO.pixel_data;
		case '1':
			return (short int *) ONE.pixel_data;
		case '2':
			return (short int *) TWO.pixel_data;
		case '3':
			return (short int *) THREE.pixel_data;
		case '4':
			return (short int *) FOUR.pixel_data;
		case '5':
			return (short int *) FIVE.pixel_data;
		case '6':
			return (short int *) SIX.pixel_data;
		case '7':
			return (short int *) SEVEN.pixel_data;
		case '8':
			return (short int *) EIGHT.pixel_data;
		case '9':
			return (short int *) NINE.pixel_data;
		default:
			return (short int *) BLKBORDERIMAGE.pixel_data; // Incase num not found.
	}
}

/**
 * Converts a 1-3 digit number to a formatted string with 0's padded if (num < 3 digits)
 * 
 * @param sNum
 * 			The string you wish to save the result to.
 * @param num
 * 			The number you wish to convert.
 */
void numToString(char sNum[50], int num) {
	if(num < 10) {
		sprintf(sNum, "00%d", num);
	} else if(num < 100) {
		sprintf(sNum, "0%d", num);
	} else {
		sprintf(sNum, "%d", num);
	}
}

/**
 * Draws the information bar. 
 */
void drawInfoBar() {
	int livesStart = 860;
	int movesStart = 300;
	int scoreStart = 580;
	int timeStart = 20;
	int startY = 17 * 40;

	for(int i = 0; i < CELLSX; i++) drawImage(startY , (i * 40), 40, 40, (short int *) BLKBORDERIMAGE.pixel_data);

	if(state.winFlag || state.loseFlag) {
		/* Drawing Lives Left */
		int num = state.score;
		char scoreNum[50];
		numToString(scoreNum, num);
		drawImage(250, 475, 40, 80, (short int *) SCORE.pixel_data);
		for(int i = 0; i < 3; i++) {
			drawImage(250 , ((i * 40) + 555), 40, 40, getNumPicture(scoreNum[i]));
		}
	} else {
		/* Drawing Lives Left */
		drawImage(startY, livesStart, 40, 80, (short int *) LIVES.pixel_data);
		for(int i = 0; i < state.livesLeft; i++) {
			drawImage(startY , ((i * 40) + 80 + livesStart), 40, 40, (short int *) PLAYERIMAGE.pixel_data);
		}

		/* Drawing Moves Left */
		int num = state.movesLeft;
		char movesNum[50];
		numToString(movesNum, num);
		drawImage(startY, movesStart, 40, 80, (short int *) MOVES.pixel_data);
		for(int i = 0; i < 3; i++) {
			drawImage(startY , ((i * 40) + 85 + movesStart), 40, 40, getNumPicture(movesNum[i]));
		}

		/* Drawing Score */
		num = state.score;
		char scoreNum[50];
		numToString(scoreNum, num);
		drawImage(startY, scoreStart, 40, 80, (short int *) SCORE.pixel_data);
		for(int i = 0; i < 3; i++) {
			drawImage(startY , ((i * 40) + 80 + scoreStart), 40, 40, getNumPicture(scoreNum[i]));
		}

		/* Drawing Time Left */
		num = state.timeLeft;
		char timeNum[50];
		numToString(timeNum, num);
		drawImage(startY, timeStart, 40, 80, (short int *) TIME.pixel_data);
		for(int i = 0; i < 3; i++) {
			drawImage(startY , ((i * 40) + 80 + timeStart), 40, 40, getNumPicture(timeNum[i]));
		}
	}
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
        while(state.showStartMenu || state.showGameMenu || state.winFlag || state.loseFlag) {}
		delay(625);
		for (int i = 0; i < (CELLSY * CELLSX); i++) {
			int x = state.objs[i].posX;
			int v = state.objs[i].velocity;
			if (v != 0) {
				if((x + v) < CELLSX && (x + v) >= 0) {
					x = x + v;
				} else {
					if((x + v) >= CELLSX) x = 0;
					else x = CELLSX - 1;
				}
			}
			updateCell(&state, state.objs[i].type, state.objs[i].posY, x, v, i);
		}
		int x = state.player.posX;
		int v = state.player.velocity;
		if(v != 0) {
			if((x + v) < CELLSX && (x + v) >= 0) {
				x = x + v;
				updatePlayer(&state, PLAYER, state.player.posY, x, v);
			} else {
				state.livesLeft -= 1;
                if(state.livesLeft <= 0) {
					state.updateScreen = true;
                    state.loseFlag = true;
                }
                state.scene = 1;
                updatePlayer(&state, PLAYER, 21, (CELLSX / 2), 0);
			}
		}
		checkCell(&state);
    }
}

/**
 * The function the will handle the draw thread. 
 */
void * drawThread() {
	state.refreshScreen = true;
	while(true) {
		while(!state.refreshScreen) {}
		if(state.showStartMenu) { // Checks if we are in the start menu.
			drawStartScreen();
		} else if(state.winFlag || state.loseFlag) {
			int score = (state.timeLeft + state.movesLeft + state.livesLeft) * 1.4;
			if(state.winFlag && (state.score < score)) state.score = score;
			if(state.updateScreen) {
				updateGameMap(&state);
				refreshBoard();
				state.updateScreen = false;
			}
			drawWinLoseBanner();
			drawInfoBar();
		} else if(state.showGameMenu) {
			drawPauseMenu();
		} else {
			refreshBoard();
			drawInfoBar();
		}
		drawFB();
		state.refreshScreen = false;
	}
}

/**
 * The function the will handle the controller thread. 
 */
void * controllerThread() {
	while(true) {
		int button = getButtonPressed(gpioPtr);
		if(state.showStartMenu) { // Checks if we are in the start menu.
			if((button == JD) && (activeButton == 1)) {
				activeButton = 2;
				state.refreshScreen = true;
			} else if((button == JU) && (activeButton == 2)) {
				activeButton = 1;
				state.refreshScreen = true;
			} else if((button == A) && (activeButton == 1)) { // Starts game.
				state.showStartMenu = false;
				activeButton = 1;
				state.refreshScreen = true;
			} else if((button == A) && (activeButton == 2)) { // Exits game.
				state.gameOver = true;
				state.refreshScreen = true;
			}
		} else if(state.winFlag || state.loseFlag) {
			if(button != -1) {
				state.showStartMenu = true;
				initState(&state);
				state.refreshScreen = true;
			}
		} else if(state.showGameMenu) { // Checks if the game is paused.
			if((button == JD) && (activeButton == 1)) {
				activeButton = 2;
				state.refreshScreen = true;
			} else if((button == JU) && (activeButton == 2)) {
				activeButton = 1;
				state.refreshScreen = true;
			} else if((button == A) && (activeButton == 1)) { // Restarts game
				initState(&state);
				state.showStartMenu = false;
				state.showGameMenu = false;
				state.refreshScreen = true;
			} else if((button == A) && (activeButton == 2)) { // Quits game & displays start menu.
				state.showGameMenu = false;
				state.showStartMenu = true;
				state.refreshScreen = true;
				initState(&state);
			} else if((button == STR)) {
				state.showGameMenu = false;
				activeButton = 1;
				state.refreshScreen = true;
			}
		} else {
			if(button == STR) { // Pauses the game.
				state.showGameMenu = true;
				state.refreshScreen = true;
			} else {
				if((button == JU) || (button == JD) || (button == JR) || (button == JL)) {
					movePlayer(&state, button);
				}
			}
		}
	}
}

/**
 * The function that will handle the time thread. 
 */
void * timeThread() {
	while(true) {
		while(state.showStartMenu || state.showGameMenu || state.winFlag || state.loseFlag) {}
		int timeLeft = state.timeLeft;
		timeLeft -= 1;
		state.timeLeft = timeLeft;
		int timePlaying = state.timePlaying;
		timePlaying += 1;
		state.timePlaying = timePlaying;
		if(state.timeLeft <= 0) {
			state.updateScreen = true;
			state.loseFlag = true;
		}
		if((state.timePlaying == 30)) {
			state.timePlaying = 0;
			int x = getRandomNum(&state, 1, (CELLSX - 2));
			int y;
			switch(state.highestLevel) {
				case 1:
					y = getRandomNum(&state, 17, 20);
					break;
				case 2:
					y = getRandomNum(&state, 12, 15);
					break;
				case 3:
					y = getRandomNum(&state, 7, 10);
					break;
				case 4:
					y = getRandomNum(&state, 2, 5);
					break;
			}
			int type = getRandomNum(&state, 1, 5);
			switch(type) {
				case 1:
					updateValuePack(&state, y, x, VALUEPACK1);
					break;
				case 2:
					updateValuePack(&state, y, x, VALUEPACK2);
					break;
				case 3:
					updateValuePack(&state, y, x, VALUEPACK3);
					break;
				case 4:
					updateValuePack(&state, y, x, VALUEPACK4);
					break;
				case 5:
					updateValuePack(&state, y, x, VALUEPACK5);
					break;
			}
			state.refreshScreen = true;
		}
		sleep(1);
	}
}
