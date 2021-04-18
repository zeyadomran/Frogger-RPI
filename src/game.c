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
    for(int i = 0; i < CELLSY; i++) {
        for(int j = 0; j < CELLSX; j++) {
            switch(i) {
            case 0:
                if((j % 2) == 0) updateCell(state, CASTLE, i, j, 0);
                else updateCell(state, WINZONE, i, j, 0);
                break;
            // Challenge 4
            case 1:
                randNum = getRandomNum(0, 4);
                if(randNum == 1) updateCell(state, ZOMBIE2, i, j, -2);
                else updateCell(state, TILE, i, j, -2);
                break;
            case 2:
                randNum = getRandomNum(0, 4);
                if(randNum == 1) updateCell(state, ZOMBIE1, i, j, 2);
                else updateCell(state, TILE, i, j, 2);
                break;
            case 3:
                randNum = getRandomNum(0, 4);
                if(randNum == 1) updateCell(state, ZOMBIE2, i, j, -1);
                else updateCell(state, TILE, i, j, -1);
                break;
            case 4:
                randNum = getRandomNum(0, 4);
                if(randNum == 1) updateCell(state, ZOMBIE1, i, j, 1);
                else updateCell(state, TILE, i, j, 1);
                break;
            case 5:
                updateCell(state, REDBORDER, i, j, 0);
                break;
            // Challenge 3
            case 6:
                randNum = getRandomNum(0, 4);
                if(randNum == 1) updateCell(state, SPACESHIP1, i, j, 2);
                else updateCell(state, SPACE, i, j, 2);
                break;
            case 7:
                randNum = getRandomNum(0, 4);
                if(randNum == 1) updateCell(state, SPACESHIP2, i, j, -1);
                else updateCell(state, SPACE, i, j, -1);
                break;
            case 8:
                randNum = getRandomNum(0, 4);
                if(randNum == 1) updateCell(state, SPACESHIP1, i, j, 1);
                else updateCell(state, SPACE, i, j, 1);
                break;
            case 9:
                updateCell(state, GRNBORDER, i, j, 0);
                break;
            // Challenge 2
            case 10:
                randNum = getRandomNum(0, 4);
                if(randNum == 1) updateCell(state, LOG, i, j, -2);
                else updateCell(state, WATER, i, j, -2);
                break;
            case 11:
                randNum = getRandomNum(0, 4);
                if(randNum == 1) updateCell(state, LOG, i, j, 1);
                else updateCell(state, WATER, i, j, 1);
                break;
            case 12:
                randNum = getRandomNum(0, 4);
                if(randNum == 1) updateCell(state, TURTLE, i, j, 1);
                else updateCell(state, WATER, i, j, 1);
                break;
            case 13:
                updateCell(state, BLUBORDER, i, j, 0);
                break;
            // Challenge 1
            case 14:
                randNum = getRandomNum(0, 4);
                if(randNum == 1) updateCell(state, CAR2, i, j, 2);
                else updateCell(state, ROAD, i, j, 2);
                break;
            case 15:
                randNum = getRandomNum(0, 4);
                if(randNum == 1) updateCell(state, CAR1, i, j, -1);
                else updateCell(state, ROAD, i, j, -1);
                break;
            case 16:
                randNum = getRandomNum(0, 4);
                if(randNum == 1) updateCell(state, CAR2, i, j, 1);
                else updateCell(state, ROAD, i, j, 1);
                break;
            // Player Starting pos & border & info
            case 17:
                if(j == (CELLSX / 2)) {
                    updatePlayer(state, PLAYER, i, j, 0);
                    updateCell(state, BLKBORDER, i, j, 0); 
                } else {
                    updateCell(state, BLKBORDER, i, j, 0);
                }
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
 * @param y
 *              The y index of the object.
 * @param x
 *              The x index of the object.
 * @param velocity
 *              The velocity of the object.
 */
void updateCell(shared * state, char type, int y, int x, int velocity) {
    state->objs[y*x].type = type;
    state->objs[y*x].posX = x;
    state->objs[y*x].posY = y;
    state->objs[y*x].velocity = velocity;
    state->gameMap.objects[y][x].type = type;
    state->gameMap.objects[y][x].posX = x;
    state->gameMap.objects[y][x].posY = y;
    state->gameMap.objects[y][x].velocity = velocity;
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
    // Allocating Memory
    state = malloc(sizeof (shared));
    state->gameMap.objects = (Object **) malloc(sizeof (Object* ) * CELLSY);
    for(int i = 0; i < CELLSX; i++) state->gameMap.objects[i] = (Object * ) malloc(sizeof (Object) * CELLSX);
    state->objs = (Object * ) malloc((CELLSX * CELLSY) * sizeof (Object));

    // Initializing the rest
    state->showStartMenu = true;
    state->showGameMenu = false;
    state->score = 0;
    state->livesLeft = 4;
    state->movesLeft = 99;
    state->winFlag = false;
    state->loseFlag = false;
    state->timeLeft = -1;
    state->startTime = time(0);
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
    Object * player = &state->player;
    switch(direction) {
        case JU:
            if(player->posY != 0) {
                player->posY += 1;
            }
            break;
        case JD:
            if(player->posY != 17) {
                player->posY -= 1;
            }
            break;
        case JL:
            if(player->posX != 0) {
                player->posX -= 1;
            }
            break;
        case JR:
            if(player->posX != (CELLSX - 1)) {
                player->posX += 1;
            }
            break;
    }
    checkCell(state);
}

/**
 * Checks the cell the player is currently in.
 * 
 * @param state
 *              The game's state. 
 */
void checkCell(shared * state) {
    Object * player = &state->player;
    for(int i = 0; i < (CELLSX * CELLSY); i++) {
        if(player->posY == state->objs[i].posY) {
            char type = state->objs[i].type;
            if((type == CAR1) ||(type == CAR2) ||(type == WATER) || (type == ZOMBIE1) || (type == ZOMBIE2) || (type == SPACESHIP1) || (type == SPACESHIP2) || (type == CASTLE)) {
                state->loseFlag = true;
            } else if((type == WINZONE)) {
                state->winFlag = true;
            } else {
                player->posX = state->objs[i].posX;
                player->posY = state->objs[i].posY;
                player->velocity = state->objs[i].velocity;
                updatePlayer(state, PLAYER, player->posY, player->posX, player->velocity);
            } 
        }
    }
}
