#ifndef game
#define game

/* Definitions */

/* Amount of cells in game map, each cell is 40x40 pixels large. */ 
#define CELLSX      32
#define CELLSY      18

/* Object type definitions. */
#define CASTLE      'C'
#define BLUBORDER   'B'
#define REDBORDER   'R'
#define GRNBORDER   'G'
#define BLKBORDER   'K'
// Challenge 4
#define ZOMBIE1     'Z'
#define ZOMBIE2     'Y'
#define TILE        'T'
// Challenge 3
#define SPACESHIP1  'S'
#define SPACESHIP2  'Q'
#define SPACE       'O'
// Challenge 2
#define LOG         'L'
#define TURTLE      'N'
#define WATER       'W'
// Challenge 1
#define CAR1        'V'
#define CAR2        'X'
#define ROAD        'I'
#define PLAYER      'P'
#define INFO        'U'

/* A struct of the game's objects. */
typedef struct {
    char type[CELLSY][CELLSX];
    int posX[CELLSY][CELLSX];
    int posY[CELLSY][CELLSX];
    int velocity[CELLSY][CELLSX];
} Object;

/* The game's shared struct. */
typedef struct {
    Object gameMap;
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

void loadGameMap(shared * state);
void updateCell(shared * state, char type, int x, int y, int velocity);
void initState(shared * state);
int getRandomNum(int lowerLimit, int upperLimit);

#endif