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
    // Utility Variables
    // These are used to make the map random but consistant.
    int randNum;
    int counter = 0;
    int temp = 0;
    int lastLog1 = 0;
    int lastLog2 = 0;
    int lastTurtle1 = 0;
    int lastTurtle2 = 0;
    for(int i = 0; i < CELLSY; i++) {
        for(int j = 0; j < CELLSX; j++) {
            switch(i) {
            case 0:
                updateCell(state, CASTLE, i, j, 0, counter);
                break;
            case 1:
                if(temp <= 2) {
                    updateCell(state, CASTLE, i, j, 0, counter);
                    temp++;
                } else if(temp <= 4) {
                    updateCell(state, WINZONE, i, j, 0, counter);
                    temp++;
                    if(temp == 5) temp = 0;
                }
                break;
            // Challenge 4
            case 2:
                randNum = getRandomNumNONTHREADS(0, 6);
                if(randNum == 1) updateCell(state, ZOMBIE2, i, j, -1, counter);
                else updateCell(state, TILE, i, j, -1, counter);
                break;
            case 3:
                randNum = getRandomNumNONTHREADS(0, 6);
                if(randNum == 1) updateCell(state, ZOMBIE1, i, j, 1, counter);
                else updateCell(state, TILE, i, j, 1, counter);
                break;
            case 4:
                randNum = getRandomNumNONTHREADS(0, 6);
                if(randNum == 1) updateCell(state, ZOMBIE2, i, j, -1, counter);
                else updateCell(state, TILE, i, j, -1, counter);
                break;
            case 5:
                randNum = getRandomNumNONTHREADS(0, 6);
                if(randNum == 1) updateCell(state, ZOMBIE1, i, j, 1, counter);
                else updateCell(state, TILE, i, j, 1, counter);
                break;
            case 6:
                updateCell(state, PURBORDER, i, j, 0, counter);
                break;
            // Challenge 3
            case 7:
                randNum = getRandomNumNONTHREADS(0, 6);
                if(randNum == 1) updateCell(state, SPACESHIP2, i, j, -1, counter);
                else updateCell(state, SPACE, i, j, -1, counter);
                break;
            case 8:
                randNum = getRandomNumNONTHREADS(0, 6);
                if(randNum == 1) updateCell(state, SPACESHIP1, i, j, 1, counter);
                else updateCell(state, SPACE, i, j, 1, counter);
                break;
            case 9:
                randNum = getRandomNumNONTHREADS(0, 6);
                if(randNum == 1) updateCell(state, SPACESHIP2, i, j, -1, counter);
                else updateCell(state, SPACE, i, j, -1, counter);
                break;
            case 10:
                randNum = getRandomNumNONTHREADS(0, 6);
                if(randNum == 1) updateCell(state, SPACESHIP1, i, j, 1, counter);
                else updateCell(state, SPACE, i, j, 1, counter);
                break;
            case 11:
                updateCell(state, PURBORDER, i, j, 0, counter);
                break;
            // Challenge 2
            case 12:
                if(lastTurtle2 <= 1) {
                    randNum = getRandomNumNONTHREADS(0, 1);
                    if(randNum == lastTurtle2) {
                        updateCell(state, TURTLE, i, j, 1, counter);
                    }
                    lastTurtle2++;
                } else if(lastTurtle2 > 3) {
                    updateCell(state, WATER, i, j, 1, counter);
                    randNum = getRandomNumNONTHREADS(1, 3);
                    if(randNum == 2) {
                        lastTurtle2 = 0;
                    }
                }
                break;
            case 13:
                if(lastLog1 <= 2) {
                    randNum = getRandomNumNONTHREADS(0, 2);
                    if(randNum == lastLog1) {
                        updateCell(state, LOG, i, j, -1, counter);
                    }
                    lastLog1++;
                } else if(lastLog1 > 2) {
                    updateCell(state, WATER, i, j, -1, counter);
                    randNum = getRandomNumNONTHREADS(1, 3);
                    if(randNum == 2) {
                        lastLog1 = 0;
                    }
                }
                break;
            case 14:
                if(lastLog2 <= 2) {
                    randNum = getRandomNumNONTHREADS(0, 2);
                    if(randNum == lastLog2) {
                        updateCell(state, LOG, i, j, 1, counter);
                    }
                    lastLog2++;
                } else if(lastLog2 > 2) {
                    updateCell(state, WATER, i, j, 1, counter);
                    randNum = getRandomNumNONTHREADS(1, 3);
                    if(randNum == 2) {
                        lastLog2 = 0;
                    }
                }
                break;
            case 15:
                if(lastTurtle1 <= 2) {
                    updateCell(state, TURTLE, i, j, -1, counter);
                    lastTurtle1++;
                } else if(lastTurtle1 <= 4) {
                    updateCell(state, WATER, i, j, -1, counter);
                    lastTurtle1++;
                    if(lastTurtle1 == 5) lastTurtle1 = 0;
                }
                break;
            case 16:
                updateCell(state, PURBORDER, i, j, 0, counter);
                break;
            // Challenge 1
            case 17:
                randNum = getRandomNumNONTHREADS(0, 6);
                if(randNum == 1) updateCell(state, CAR1, i, j, -1, counter);
                else updateCell(state, ROAD, i, j, -1, counter);
                break;
            case 18:
                randNum = getRandomNumNONTHREADS(0, 6);
                if(randNum == 1) updateCell(state, CAR2, i, j, 1, counter);
                else updateCell(state, ROAD, i, j, 1, counter);
                break;
            case 19:
                randNum = getRandomNumNONTHREADS(0, 6);
                if(randNum == 1) updateCell(state, CAR1, i, j, -1, counter);
                else updateCell(state, ROAD, i, j, -1, counter);
                break;
            case 20:
                randNum = getRandomNumNONTHREADS(0, 6);
                if(randNum == 1) updateCell(state, CAR2, i, j, 1, counter);
                else updateCell(state, ROAD, i, j, 1, counter);
                break;
            // Player Starting pos & border & info
            case 21:
                if(j == (CELLSX / 2)) {
                    updateCell(state, PURBORDER, i, j, 0, counter); 
                    updatePlayer(state, PLAYER, i, j, 0);
                } else {
                    updateCell(state, PURBORDER, i, j, 0, counter);
                }
                break;
            }
            counter += 1;
        }
    }
    updateValuePack(state, 0, 0, VALUEPACK1);
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
 * Get a random number in a certain range for threads only.
 * 
 * @param state
 *              The game's state.
 * @param lowerLimit
 *              The lowest number you wish to get.
 * @param upperLimit
 *              The highest number you wish to get.
 * @return The number generated.
*/
int getRandomNum(shared * state, int lowerLimit, int upperLimit) { 
    // I got this from the rand_r docs since rand_r wasn't working for me when i call it from a thread
    // https://code.woboq.org/userspace/glibc/stdlib/rand_r.c.html
    unsigned int next = state->seed;
    int result;
    next *= 1103515245;
    next += 12345;
    result = (unsigned int) (next / 65536) % 2048;
    next *= 1103515245;
    next += 12345;
    result <<= 10;
    result ^= (unsigned int) (next / 65536) % 1024;
    next *= 1103515245;
    next += 12345;
    result <<= 10;
    result ^= (unsigned int) (next / 65536) % 1024;
    state->seed = next;
    return (((result % ((upperLimit - lowerLimit + 1))) + lowerLimit)); 
} 

/**
 * Get a random number in a certain range for non threads.
 * 
 * @param lowerLimit
 *              The lowest number you wish to get.
 * @param upperLimit
 *              The highest number you wish to get.
 * @return The number generated.
*/
int getRandomNumNONTHREADS(int lowerLimit, int upperLimit) { return ((rand() % ((upperLimit - lowerLimit + 1))) + lowerLimit); } 

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
    state->scene = 1;
    state->seed = (unsigned int) time(0);
    state->livesLeft = 4;
    state->movesLeft = 100;
    state->highestLane = 21;
    state->winFlag = false;
    state->loseFlag = false;
    state->timeLeft = 240;
    state->timePlaying = 0;
    loadGameMap(state);
}

/**
 * Updates a ValuePack to be displayed on the game map. 
 * 
 * @param state
 *          The game's state.
 * @param y
 *          The y position of the ValuePack.
 * @param x
 *          The x position of the ValuePack.
 * @param type
 *          The type of ValuePack.
 */
void updateValuePack(shared * state, int y, int x, char type) {
    state->valuePack.type = type;
    state->valuePack.posY = y;
    state->valuePack.posX = x;
    state->valuePack.velocity = 0;
    if(!(y == 0) && !(x == 0)) {
        state->gameMap[y][x] = type;
    }
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
            if(y > 1) {
                y -= 1;
                if(y < state->highestLane) {
                    state->score += 10;
                    state->highestLane = y;
                }
                playerMoved = true;
            }
            break;
        case JD:
            if(y < (CELLSY - 1)) {
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
            if(x < (CELLSX - 1)) {
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
 * Checks a player collision with a ValuePack
 * 
 * @param state
 *              The game's state. 
 */
void checkValuePack(shared * state) {
    if((state->player.posX == state->valuePack.posX) && (state->player.posY == state->valuePack.posY)) {
        char type = state->valuePack.type;
        int lives;
        int timeLeft;
        int score;
        switch(type) {
            case VALUEPACK1:
                state->movesLeft += 5;
                break;
            case VALUEPACK2:
                state->movesLeft += 10;
                timeLeft = state->timeLeft + 10;
                state->timeLeft = timeLeft;
                break;
            case VALUEPACK3:
                state->movesLeft += 15;
                timeLeft = state->timeLeft + 15;
                state->timeLeft = timeLeft;
                if(state->livesLeft < 6) {
                    lives = state->livesLeft + 1;
                    state->livesLeft = lives;
                }
                break;
            case VALUEPACK4:
                score = state->score + 50;
                state->score = score;
                break;
            case VALUEPACK5:
                if(state->livesLeft < 6) {
                    lives = state->livesLeft + 2;
                    state->livesLeft = lives;
                }
                break;
        }
        updateValuePack(state, 0, 0, VALUEPACK1);
    } else {
        updateValuePack(state, state->valuePack.posY, state->valuePack.posX, state->valuePack.type);
    }
}

/**
 * Checks the cell the player is currently in.
 * 
 * @param state
 *              The game's state. 
 */
void checkCell(shared * state) {
    int y = state->player.posY;
    int x = state->player.posX;
    checkValuePack(state);
    for(int i = 0; i < (CELLSX * CELLSY); i++) {
        int objY = state->objs[i].posY;
        int objX = state->objs[i].posX;
        if((y == objY) && x == objX) {
            char type = state->objs[i].type;
            if(
                (type == CAR1) || 
                (type == CAR2) || 
                (type == WATER) || 
                (type == ZOMBIE1) || 
                (type == ZOMBIE2) || 
                (type == SPACESHIP1) || 
                (type == SPACESHIP2) || 
                (type == CASTLE)
            ) {
                state->livesLeft -= 1;
                if(state->livesLeft <= 0) {
                    state->loseFlag = true;
                }
                state->scene = 1;
                updatePlayer(state, PLAYER, 21, (CELLSX / 2), 0);
            } else if(type == WINZONE) {
                state->winFlag = true;
            } else if((type == LOG) || (type == TURTLE)) {
                updatePlayer(state, PLAYER, y, x, state->objs[i].velocity);
            } else {
                updatePlayer(state, PLAYER, y, x, 0);
            }
        }
    }
    if(state->player.posY <= 6) {
        state->scene = 2;
    } else if(state->player.posY <= 11) {
        state->scene = 1;
    }
}
