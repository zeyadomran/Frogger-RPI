#ifndef game
#define game

/* Definitions */

/* Amount of cells in game map, each cell is 35x35 pixels large. */ 
#define CELLSX      32
#define CELLSY      18

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
void updateGameMap(shared state, char *type, int x, int y, int velocity);
void initState(shared state);

#endif