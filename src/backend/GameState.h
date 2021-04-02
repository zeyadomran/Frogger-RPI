#ifndef GameState
#define GameState

/* Definitions */
struct state {
    int scene;
    int score;
    int livesLeft;
    int movesLeft;
    bool winFLag;
    bool loseFlag;
    int timeLeft;
};

// temp
int getState(void);

#endif