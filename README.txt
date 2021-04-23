CPSC 359 Project Part 2.
Created by: Zeyad Omran (30096692) and Mohamed El Hefnawy (30093687).

<IMPORTANT>
    The framebuffer must be set to 1280 x 720 and 16bpp; Otherwise the game will not work as required.
</IMPORTANT>

To run:
    -   cd into the directory <Frogger-RPI>
    -   use the `make` command to compile the source code
    -   use `./froggerGame` to run the game

Useful things to know:
    -   We have implemented 5 different value packs that spawn every 30 seconds at the highest level you reached (4 Levels in game).
        +   Value Pack 1:   Gives an extra 5 moves.
        +   Value Pack 2:   Gives an extra 10 moves & 10 seconds added to time.
        +   Value Pack 3:   Gives an extra 15 moves & 15 seconds added to time & an extra life (MAX 6 Lives). 
        +   Value Pack 4:   Adds 50 points to your score.
        +   Value Pack 5:   Gives an extra life (MAX 6 Lives).
    -   We implemented to scenes that are displayed based on the players position.
    -   To win you must go to the gap in the castle (Looks like tiles between the green castle walls).
        +   If you hit the green walls, you will lose a life and start over.
    -   Controls are as specified in the project PDF on d2l.
    -   We used 4 different threads in our project.
        +   Objects Thread:     This thread updates the positions of all objects on the map.
        +   Draw Thread:        This thread handles the drawing to the framebuffer.
        +   Controller Thread:  This thread handles the user input from the SNES controller.
        +   Time Thread:        This thread ticks down the time every second, and creates a value pack every 30 seconds.

Happy Gaming!
