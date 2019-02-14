#ifndef _board_h
#define _board_h

#include <cstdlib>
#include <iostream>
#include <vector>
#include "Cell.h"
#include <random>

#ifdef _WIN32
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#endif // 

#ifdef __unix__
#include <unistd.h>
#include <termios.h>

extern struct termios orig_termios;
void disableRawMode();
void enableRawMode();

#endif


extern const unsigned int dimension;


extern int score;



enum Choice {
    QUIT = 0,
    RIGHT,
    LEFT,
    UP,
    DOWN
};

class Board {
public:
    void initBoard();
    void getChoice(int ch);
    void play();

private:
    int choose();
    void drawBoard();
    int randVal();
    void newCell(int);
    bool noMove();
    int generateRandom(std::vector<int>& candidates);
    bool noFreeCells();

    void compressLeft();
    void compressRight();
    void compressDown();
    void compressUp();

    void joinLeft();
    void joinRight();
    void joinUp();
    void joinDown();

    void left();
    void right();
    void up();
    void down();

    void gameOver();
    void quit();
private:
    std::vector<Cell> mBoard;
    bool moved = false;
};

#endif


