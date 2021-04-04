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

            if(i == (CELLSY - 2)) {
                if(j == (CELLSX / 2)) updateGameMap(state, "PLAYER", i, j, 0); 
                else updateGameMap(state, "CBORDER", i, j, 0);
            } else if(i == (CELLSY - 1)) updateGameMap(state, "INFO", i, j, 0);
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
void updateGameMap(shared state, char *type, int x, int y, int velocity) {
    state.gameMap[y][x]->type = type;
    state.gameMap[y][x]->posX = x;
    state.gameMap[y][x]->posY = y;
    state.gameMap[y][x]->velocity = velocity;
}

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
