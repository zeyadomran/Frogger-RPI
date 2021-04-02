#ifndef game
#define game

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

/* The game's shared struct. */
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

/* Prototypes */
void changeScene(void);
void loadGameMap(void);
void initializeState(void);
struct gameState getState(void);

#endif