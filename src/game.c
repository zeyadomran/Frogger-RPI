#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* Definitions */
#define CELLSX      36
#define CELLSY      20

/* Defining different tiles for the game map */
#define SAFEZONE    0
#define CASTLE      1
#define FROG        2
#define ROAD        3
#define WATER       4
#define CAR1        5
#define CAR2        6
#define TRUCK       7
#define LILYPAD     8
#define SMALLLOG    9
#define LARGELOG    10
#define LIFEVP      11
#define MOVEVP      12

/* Defining Start & Game menu tiles */
#define BLACKBG     -1
#define CREATORS    -2
#define TITLE       -3
#define STARTGAME   -4
#define RESTARTGAME -5
#define QUITGAME    -6

/* Prototypes */
void changeScene(void);
void loadGameMap(void);
void initializeState(void);
struct gameState getState(void);


struct gameState {
    int gameMap[CELLSX][CELLSY];
    int scene;
    bool showGameMenu;
    int score;
    int livesLeft;
    int movesLeft;
    bool winFlag;
    bool loseFlag;
    int timeLeft;
    int startTime;
};

/* Global Variables */
struct gameState state;

void loadGameMap(void) {
    if(state.scene == 0) {
        for(int i = 0; i < CELLSY; i++) {
            for(int j = 0; j < CELLSX; j++) {
                state.gameMap[i][j] = BLACKBG;
                if((i >= 2) && (i <= 5) && (j >= 9) && (j <= 18)) state.gameMap[i][j] = TITLE;
                if((i >= 7) && (i <= 9) && (j >= 16) && (j <= 20)) state.gameMap[i][j] = STARTGAME;
                if((i >= 11) && (i <= 13) && (j >= 16) && (j <= 20)) state.gameMap[i][j] = QUITGAME;
                if((i == (CELLSY - 1)) && (j <= 17)) state.gameMap[i][j] = CREATORS;
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