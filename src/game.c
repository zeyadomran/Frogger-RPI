#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"

/**
 * Load's the Game Map based on the current scene.
 * 
 * @param state The current state.
 */
void loadGameMap(shared state) {
   if(state.showStartMenu) {
       for(int i = 0; i < CELLSY; i++) {
           for(int j = 0; j < CELLSX; j++) {
           }
       }
   } else if(state.showStartMenu) {

   } else {

   }
}

void initState(shared state) {
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
