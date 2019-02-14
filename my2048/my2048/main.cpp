#include "Board.h"

int main() {

    Board *board = new Board();
    board->initBoard();
    board->play();
    delete board;
}
