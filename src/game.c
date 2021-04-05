#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"

/**
 * Load's the Game Map based on the current scene.
 * 
 * @param state 
 *              The current state.
 */
void loadGameMap(shared state) {
    for(int i = 0; i < CELLSY; i++) {
        for(int j = 0; j < CELLSX; j++) {
            switch(i) {
            case 0:
                if((j % 2) == 0) updateCell(state, CASTLE, i, j, 0);
                else updateCell(state, BLUBORDER, i, j, 0);
                break;
            // Challenge 4
            case 1:
                int randNum = getRandomNum(0, 1);
                if(randNum == 1) updateCell(state, ZOMBIE2, i, j, -2);
                else updateCell(state, TILE, i, j, -2);
                break;
            case 2:
                int randNum = getRandomNum(0, 1);
                if(randNum == 1) updateCell(state, ZOMBIE1, i, j, 2);
                else updateCell(state, TILE, i, j, 2);
                break;
            case 3:
                int randNum = getRandomNum(0, 1);
                if(randNum == 1) updateCell(state, ZOMBIE2, i, j, -1);
                else updateCell(state, TILE, i, j, -1);
                break;
            case 4:
                int randNum = getRandomNum(0, 1);
                if(randNum == 1) updateCell(state, ZOMBIE1, i, j, 1);
                else updateCell(state, TILE, i, j, 1);
                break;
            case 5:
                updateCell(state, REDBORDER, i, j, 0);
                break;
            // Challenge 3
            case 6:
                int randNum = getRandomNum(0, 1);
                if(randNum == 1) updateCell(state, SPACESHIP1, i, j, 2);
                else updateCell(state, SPACE, i, j, 2);
                break;
            case 7:
                int randNum = getRandomNum(0, 1);
                if(randNum == 1) updateCell(state, SPACESHIP2, i, j, -1);
                else updateCell(state, SPACE, i, j, -1);
                break;
            case 8:
                int randNum = getRandomNum(0, 1);
                if(randNum == 1) updateCell(state, SPACESHIP1, i, j, 1);
                else updateCell(state, SPACE, i, j, 1);
                break;
            case 9:
                updateCell(state, GRNBORDER, i, j, 0);
                break;
            // Challenge 2
            case 10:
                int randNum = getRandomNum(0, 1);
                if(randNum == 1) updateCell(state, LOG, i, j, -2);
                else updateCell(state, WATER, i, j, -2);
                break;
            case 11:
                int randNum = getRandomNum(0, 1);
                if(randNum == 1) updateCell(state, LOG, i, j, 1);
                else updateCell(state, WATER, i, j, 1);
                break;
            case 12:
                int randNum = getRandomNum(0, 1);
                if(randNum == 1) updateCell(state, LILYPAD, i, j, 1);
                else updateCell(state, WATER, i, j, 1);
                break;
            case 13:
                updateCell(state, BLUBORDER, i, j, 0);
                break;
            // Challenge 1
            case 14:
                int randNum = getRandomNum(0, 1);
                if(randNum == 1) updateCell(state, CAR1, i, j, 2);
                else updateCell(state, ROAD, i, j, 2);
                break;
            case 15:
                int randNum = getRandomNum(0, 1);
                if(randNum == 1) updateCell(state, CAR2, i, j, -1);
                else updateCell(state, ROAD, i, j, -1);
                break;
            case 16:
                int randNum = getRandomNum(0, 1);
                if(randNum == 1) updateCell(state, CAR1, i, j, 1);
                else updateCell(state, ROAD, i, j, 1);
                break;
            // Player Starting pos & border & info
            case 17:
                if(j == (CELLSX / 2)) updateCell(state, PLAYER, i, j, 0); 
                else updateCell(state, BLKBORDER, i, j, 0);
                break;
            case 18:
                updateCell(state, INFO, i, j, 0);
                break;
            }
        }
    }
}

/**
 * Updates the gameMap at a certain index.
 * 
 * @param state
 *              The current state.
 * @param type
 *              The type of the object.
 * @param x
 *              The x index of the object.
 * @param y
 *              The y index of the object.
 * @param velocity
 *              The velocity of the object.
 */
void updateCell(shared state, char *type, int x, int y, int velocity) {
    state.gameMap[y][x]->type = type;
    state.gameMap[y][x]->posX = x;
    state.gameMap[y][x]->posY = y;
    state.gameMap[y][x]->velocity = velocity;
}

/**
 * Get a random number in a certain range.
 * 
 * @param lowerLimit
 *              The lowest number you wish to get.
 * @param upperLimit
 *              The highest number you wish to get.
 * @return The number generated.
*/
int getRandomNum(int lowerLimit, int upperLimit) { return ((rand() % ((upperLimit - lowerLimit + 1))) + lowerLimit); } 

/**
 * Initializes the state.
 * 
 * @param state
 *              The State you wish to initialize. 
 */
void initState(shared state) {
    for(int i = 0; i < CELLSY; i++) {
        for(int j = 0; j < CELLSX; j++) {
            state.gameMap[i][j] = (Object ***) malloc(sizeof(Object));
        }
    }
    state.showStartMenu = true;
    state.showGameMenu = false;
    state.score = 0;
    state.livesLeft = 4;
    state.movesLeft = 20;
    state.winFlag = false;
    state.loseFlag = false;
    state.timeLeft = -1;
    state.startTime = time(0);
    loadGameMap(state);
}
