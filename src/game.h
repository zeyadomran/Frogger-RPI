#ifndef game
#define game

/* Definitions */

/* Amount of cells in game map, each cell is 35x35 pixels large. */ 
#define CELLSX      32
#define CELLSY      18

/* Object type definitions. */
#define CASTLE      "CASTLE"
#define BLUBORDER   "BLUBORDER"
#define REDBORDER   "REDBORDER"
#define GRNBORDER   "GRNBORDER"
#define BLKBORDER   "BLKBORDER"
// Challenge 4
#define ZOMBIE1     "ZOMBIE1"
#define ZOMBIE2     "ZOMBIE2"
#define TILE        "TILE"
// Challenge 3
#define SPACESHIP1  "SPACESHIP1"
#define SPACESHIP2  "SPACESHIP2"
#define SPACE       "SPACE"
// Challenge 2
#define LOG         "LOG"
#define LILYPAD     "LILYPAD"
#define WATER       "WATER"
// Challenge 1
#define CAR1        "CAR1"
#define CAR2        "CAR2"
#define ROAD        "ROAD"
#define PLAYER      "PLAYER"
#define INFO        "INFO"

/* A struct of the game's objects. */
typedef struct {
    char *type;
    int posX;
    int posY;
    int velocity;
} Object;

/* The game's shared struct. */
typedef struct {
    Object * gameMap[CELLSY][CELLSX];
    bool showStartMenu;
    bool showGameMenu;
    int score;
    int livesLeft;
    int movesLeft;
    bool winFlag;
    bool loseFlag;
    int pausedTime;
    int timeLeft;
    int startTime;
} shared;

/* Prototypes */

void loadGameMap(shared state);
void updateCell(shared state, char *type, int x, int y, int velocity);
void initState(shared state);
int getRandomNum(int lowerLimit, int upperLimit);

#endif