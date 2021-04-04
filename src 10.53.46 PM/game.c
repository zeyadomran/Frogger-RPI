#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"

/* Global Variables */
struct gameState state;

void loadGameMap(void) {
    if(state.scene == 0) {
        for(int i = 0; i < CELLSY; i++) {
            for(int j = 0; j < CELLSX; j++) {
                state.gameMap[i][j] = BLACKBG;
                if((i == 12) && (j == 12)) state.gameMap[i][j] = TITLE;
                if((i == 7) &&(j == 16)) state.gameMap[i][j] = STARTGAME;
                if((i == 11) &&(j == 16)) state.gameMap[i][j] = QUITGAME;
                if((i == (CELLSY - 1)) && (j == 0)) state.gameMap[i][j] = CREATORS;
            }
        }
    }/* else if (state.scene == 1) {
        state.scene = 2;
    } else {
        state.scene = 0;
    }*/
}

void initializeState(void) {
    state.scene = 0;
    state.showGameMenu = false;
    state.score = 0;
    state.livesLeft = 4;
    state.movesLeft = 20;
    state.winFlag = false;
    state.loseFlag = false;
    state.timeLeft = -1;
    state.startTime = time(0);
    loadGameMap();
}

void changeScene(void) {
    if(state.scene == 0) {
        state.scene = 1;
    } else if (state.scene == 1) {
        state.scene = 2;
    } else {
        state.scene = 0;
    }
    loadGameMap();
}

struct gameState getState(void) {
    return state;
}