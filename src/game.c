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
void loadGameMap(shared * state) {
    int randNum;
    int counter = 0;
    for(int i = 0; i < CELLSY; i++) {
        for(int j = 0; j < CELLSX; j++) {
            switch(i) {
            case 0:
                if((j % 2) == 0) updateCell(state, CASTLE, i, j, 0, counter);
                else updateCell(state, WINZONE, i, j, 0, counter);
                break;
            // Challenge 4
            case 1:
                randNum = getRandomNum(0, 6);
                if(randNum == 1) updateCell(state, ZOMBIE2, i, j, -1, counter);
                else updateCell(state, TILE, i, j, -1, counter);
                break;
            case 2:
                randNum = getRandomNum(0, 6);
                if(randNum == 1) updateCell(state, ZOMBIE1, i, j, 1, counter);
                else updateCell(state, TILE, i, j, 1, counter);
                break;
            case 3:
                randNum = getRandomNum(0, 6);
                if(randNum == 1) updateCell(state, ZOMBIE2, i, j, -1, counter);
                else updateCell(state, TILE, i, j, -1, counter);
                break;
            case 4:
                randNum = getRandomNum(0, 6);
                if(randNum == 1) updateCell(state, ZOMBIE1, i, j, 1, counter);
                else updateCell(state, TILE, i, j, 1, counter);
                break;
            case 5:
                updateCell(state, REDBORDER, i, j, 0, counter);
                break;
            // Challenge 3
            case 6:
                randNum = getRandomNum(0, 6);
                if(randNum == 1) updateCell(state, SPACESHIP1, i, j, 1, counter);
                else updateCell(state, SPACE, i, j, 1, counter);
                break;
            case 7:
                randNum = getRandomNum(0, 6);
                if(randNum == 1) updateCell(state, SPACESHIP2, i, j, -1, counter);
                else updateCell(state, SPACE, i, j, -1, counter);
                break;
            case 8:
                randNum = getRandomNum(0, 6);
                if(randNum == 1) updateCell(state, SPACESHIP1, i, j, 1, counter);
                else updateCell(state, SPACE, i, j, 1, counter);
                break;
            case 9:
                updateCell(state, GRNBORDER, i, j, 0, counter);
                break;
            // Challenge 2
            case 10:
                randNum = getRandomNum(0, 4);
                if(randNum == 1) updateCell(state, LOG, i, j, 1, counter);
                else updateCell(state, WATER, i, j, 1, counter);
                break;
            case 11:
                randNum = getRandomNum(0, 4);
                if(randNum == 1) updateCell(state, LOG, i, j, -1, counter);
                else updateCell(state, WATER, i, j, -1, counter);
                break;
            case 12:
                randNum = getRandomNum(0, 4);
                if(randNum == 1) updateCell(state, TURTLE, i, j, -1, counter);
                else updateCell(state, WATER, i, j, -1, counter);
                break;
            case 13:
                updateCell(state, BLUBORDER, i, j, 0, counter);
                break;
            // Challenge 1
            case 14:
                randNum = getRandomNum(0, 6);
                if(randNum == 1) updateCell(state, CAR2, i, j, 1, counter);
                else updateCell(state, ROAD, i, j, 1, counter);
                break;
            case 15:
                randNum = getRandomNum(0, 6);
                if(randNum == 1) updateCell(state, CAR1, i, j, -1, counter);
                else updateCell(state, ROAD, i, j, -1, counter);
                break;
            case 16:
                randNum = getRandomNum(0, 6);
                if(randNum == 1) updateCell(state, CAR2, i, j, 1, counter);
                else updateCell(state, ROAD, i, j, 1, counter);
                break;
            // Player Starting pos & border & info
            case 17:
                if(j == (CELLSX / 2)) {
                    updateCell(state, BLKBORDER, i, j, 0, counter); 
                    updatePlayer(state, PLAYER, i, j, 0);
                } else {
                    updateCell(state, BLKBORDER, i, j, 0, counter);
                }
                break;
            case 18:
                updateCell(state, INFO, i, j, 0, counter);
                break;
            }
            counter += 1;
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
 * @param y
 *              The y index of the object.
 * @param x
 *              The x index of the object.
 * @param velocity
 *              The velocity of the object.
 * @param objsID
 *              The ID of the object
 */
void updateCell(shared * state, char type, int y, int x, int velocity, int objsID) {
    state->objs[objsID].type = type;
    state->objs[objsID].posX = x;
    state->objs[objsID].posY = y;
    state->objs[objsID].velocity = velocity;
    state->gameMap[y][x] = type;
}

/**
 * Updates the player.
 * 
 * @param state
 *              The current state.
 * @param type
 *              The type of the object.
 * @param y
 *              The y index of the object.
 * @param x
 *              The x index of the object.
 * @param velocity
 *              The velocity of the object.
 */
void updatePlayer(shared * state, char type, int y, int x, int velocity) {
    state->player.type = type;
    state->player.posX = x;
    state->player.posY = y;
    state->player.velocity = velocity;
    state->gameMap[y][x] = type;
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
void initState(shared * state) {
    // Allocating memory to stage
    state->stage = malloc((1280 * 720 * 2) + 1);
    // Initializing the rest
    state->showStartMenu = true;
    state->showGameMenu = false;
    state->gameOver = false;
    state->score = 0;
    state->livesLeft = 4;
    state->movesLeft = 99;
    state->winFlag = false;
    state->loseFlag = false;
    state->timeLeft = 240;
    srand(time(0));
    loadGameMap(state);
}

/**
 * Moves the player. 
 * 
 * @param state
 *              The game's state.
 * @param direction
 *              The direction the player will move in.
 */
void movePlayer(shared * state, int direction) {
    int y = state->player.posY;
    int x = state->player.posX;
    bool playerMoved = false;
    switch(direction) {
        case JU:
            if(y > 0) {
                y -= 1;
                playerMoved = true;
            }
            break;
        case JD:
            if(y < 17) {
                y += 1;
                playerMoved = true;
            }
            break;
        case JL:
            if(x > 0) {
                x -= 1;
                playerMoved = true;
            }
            break;
        case JR:
            if(x < CELLSX - 1) {
                x += 1;
                playerMoved = true;
            }
            break;
    }
    if(playerMoved) {
        state->movesLeft -= 1;
        if(state->movesLeft <= 0) {
            state->loseFlag = true;
        } else {
            updatePlayer(state, PLAYER, y, x, state->player.velocity);
        }
        checkCell(state);
    }
}

/**
 * Checks the cell the player is currently in.
 * 
 * @param state
 *              The game's state. 
 */
void checkCell(shared * state) {
    int counter = 0;
    int y = state->player.posY;
    int x = state->player.posX;
    for(int i = 0; i < CELLSY; i++) {
        for(int j = 0; j < CELLSX ; j++) {
            if((y == i) && x == j) {
                char type = state->objs[counter].type;
                if((type == CAR1) || (type == CAR2) || (type == WATER) || (type == ZOMBIE1) || (type == ZOMBIE2) || (type == SPACESHIP1) || (type == SPACESHIP2) || (type == CASTLE)) {
                    state->livesLeft -= 1;
                    if(state->livesLeft <= 0) {
                        state->loseFlag = true;
                    }
                    updatePlayer(state, PLAYER, 17, (CELLSX / 2), state->player.velocity);
                } else if((type == WINZONE)) {
                    state->winFlag = true;
                } else if((type == LOG) || (type == TURTLE)) {
                    updatePlayer(state, PLAYER, y, x, state->objs[counter].velocity);
                } else {
                    updatePlayer(state, PLAYER, y, x, 0);
                }
            }
            counter += 1;
        }
    }
}
