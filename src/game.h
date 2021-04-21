#ifndef game
#define game

#include "framebuffer.h" 

/* Definitions */

/* Amount of cells in game map, each cell is 40x40 pixels large. */ 
#define CELLSX      32
#define CELLSY      18

/* Object type definitions. */
#define CASTLE      'C'
#define WINZONE     'A'
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

// Value Packs
#define GIFT1       '1'
#define GIFT2       '2'
#define GIFT3       '3'
#define GIFT4       '4'
#define GIFT5       '5' 

/* SNES Controller Buttons */
#define B 	1
#define Y 	2
#define SEL 3
#define STR 4
#define JU 	5
#define JD 	6
#define JL 	7
#define JR 	8
#define A 	9
#define X 	10
#define LFT 11
#define RGH 12

typedef struct {
    char type;
    int posX;
    int posY;
    int velocity;
} Object;

/* The game's shared struct. */
typedef struct {
    char gameMap[CELLSY][CELLSX];
    Object objs[CELLSY * CELLSX];
    Object player;
    Object gift;
    char *stage;
    bool showStartMenu;
    bool showGameMenu;
    bool gameOver;
    int score;
    int livesLeft;
    int movesLeft;
    int highestLane;
    bool winFlag;
    bool loseFlag;
    int timeLeft;
    int timePlaying;
} shared;

/* Prototypes */

void loadGameMap(shared * state);
void updateCell(shared * state, char type, int x, int y, int velocity, int objsID);
void updatePlayer(shared * state, char type, int y, int x, int velocity);
void updateGift(shared * state, int y, int x, char type);
void initState(shared * state);
int getRandomNum(int lowerLimit, int upperLimit);
void movePlayer(shared * state, int direction);
void checkGift(shared * state);
void checkCell(shared * state);

#endif