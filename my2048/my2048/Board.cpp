#include "Board.h"


const unsigned int dimension = 4;

int score = 0;

std::random_device rd;
std::mt19937 rng(rd());

#ifdef __unix__
struct termios orig_termios;
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

#endif

int Board::randVal() {
    std::vector<int> numbersToChooseFrom;
    for (int i = 0; i < 20; i++) {
        if (i == 4) numbersToChooseFrom.push_back(i);
        if (i != 4) numbersToChooseFrom.push_back(2);
    }

    std::uniform_int_distribution<int> uni(0, numbersToChooseFrom.size() - 1);
    auto random_integer = uni(rng);

    return numbersToChooseFrom[random_integer];


}

void Board::compressLeft() {
    for (int x = 0; x < dimension;  x++) {
        for (int i = 0; i < dimension; i++) {
            if (mBoard[x*dimension+i].value() == 0) {
                for (int j = i + 1; j < dimension; j++) {
                    if (mBoard[x*dimension+j].value() > 0) {
                        mBoard[x*dimension+i].setValue(mBoard[x*dimension+j].value());
                        mBoard[x*dimension+j].setValue(0);
                        moved = true;
                        break;
                    }
                }
            }
        }
    }
}

void Board::joinLeft() {
    for (int x = 0; x < dimension;  x++) {
        for (int i = 0; i < dimension-1; i++) {
                    if (mBoard[x*dimension+i].value() == mBoard[x*dimension+i+1].value() && mBoard[x*dimension+i].value() != 0) {
                        mBoard[x*dimension+i].setValue(mBoard[x*dimension+i].value()*2);
                        score += mBoard[x*dimension + i].value();
                        mBoard[x*dimension+i+1].setValue(0);
                        moved = true;
                    }
        }
    }

}

void Board::compressUp() {
    for (int x = 0; x < dimension;  x++) {
        for (int i = 0; i < dimension; i++) {
            if (mBoard[x+i*dimension].value() == 0) {
                for (int j = i + 1; j < dimension; j++) {
                    if (mBoard[x+j*dimension].value() > 0) {
                        mBoard[x+i*dimension].setValue(mBoard[x+j*dimension].value());
                        mBoard[x+j*dimension].setValue(0);
                        moved = true;
                        break;
                    }
                }
            }
        }
    }
}

void Board::joinUp() {
    for (int x = 0; x < dimension;  x++) {
        for (int i = 0; i < dimension-1; i++) {
            if (mBoard[x+i*dimension].value() == mBoard[x+(i+1)*dimension].value() && mBoard[x+i*dimension].value() != 0) {
                        mBoard[x+i*dimension].setValue(mBoard[x+(i+1)*dimension].value()*2);
                        score += mBoard[x + i * dimension].value();
                        mBoard[x+(i+1)*dimension].setValue(0);
                        moved = true;
            }
        }
    }

}

void Board::compressRight() {
    for (int x = 0; x < dimension; x++) {
        for (int i = dimension - 1; i > 0; i--) {
            if (mBoard[x*dimension+i].value() == 0) {
                for (int j = i - 1; j >= 0; j--) {
                    if (mBoard[x*dimension+j].value() > 0) {
                        mBoard[x*dimension+i].setValue(mBoard[x*dimension+j].value());
                        mBoard[x*dimension+j].setValue(0);
                        moved = true;
                        break;
                    }
                }
            }
        }
    }
}

void Board::joinRight() {
    for (int x = 0; x < dimension; x++) {
        for (int i = dimension - 1; i > 0; i--) {
            if (mBoard[x*dimension+i].value() == mBoard[x*dimension+i-1].value() && mBoard[x*dimension+i].value() != 0) {
                mBoard[x*dimension+i].setValue(mBoard[x*dimension+i-1].value()*2);
                score += mBoard[x*dimension + i].value();
                mBoard[x*dimension+i-1].setValue(0);
                moved = true;
            }
        }
    }

}

void Board::compressDown() {
    for (int x = 0; x < dimension; x++) {
        for (int i = dimension - 1; i > 0; i--) {
            if (mBoard[x+i*dimension].value() == 0) {
                for (int j = i - 1; j >= 0; j--) {
                    if (mBoard[x+j*dimension].value() > 0) {
                        mBoard[x+i*dimension].setValue(mBoard[x+j*dimension].value());
                        mBoard[x+j*dimension].setValue(0);
                        moved = true;
                        break;
                    }
                }
            }
        }
    }
}

void Board::joinDown() {
    for (int x = 0; x < dimension; x++) {
        for (int i = dimension - 1; i > 0; i--) {
            if (mBoard[x+i*dimension].value() == mBoard[x+(i-1)*dimension].value() && mBoard[x+i*dimension].value() != 0) {
                mBoard[x+i*dimension].setValue(mBoard[x+(i-1)*dimension].value()*2);
                score += mBoard[x + i * dimension].value();
                mBoard[x+(i-1)*dimension].setValue(0);
                moved = true;
            }
        }
    }

}

void Board::left()
{
    compressLeft();
    joinLeft();
    compressLeft();


    if (moved) {
        newCell(randVal());
        moved = false;
    }

    if (noMove() && noFreeCells()) gameOver();

    play();

}

void Board::right()
{
    compressRight();
    joinRight();
    compressRight();

    if (moved) {
        newCell(randVal());
        moved = false;
    }

    if (noMove() && noFreeCells()) gameOver();

    play();
}

void Board::up() {
    compressUp();
    joinUp();
    compressUp();



    if (moved) {
        newCell(randVal());
        moved = false;
    }

    if (noMove() && noFreeCells()) gameOver();

    play();
}

void Board::down() {
    compressDown();
    joinDown();
    compressDown();
#ifdef _WIN32
    system("cls");
#elif defined __unix__
    system("clear");
#endif // 
    if (moved) {
        newCell(randVal());
        moved = false;
    }
    
    if (noMove() && noFreeCells()) gameOver();

    play();
}

void Board::initBoard() {
    for (int i = 0; i < 16; i++) {
        Cell cell;
        mBoard.push_back(cell);
    }
    newCell(2);
    newCell(2);

}

void Board::gameOver() {
    std::cout << std::endl << "Game Over!" << std::endl;
}


void Board::getChoice(int ch)
{
    switch (ch) {
    case QUIT:
        this->quit();
        break;
    case UP:
        up();
        break;
    case DOWN:
        down();
        break;
    case RIGHT:
        right();
        break;
    case LEFT:
        left();
        break;
    }
}
void Board::quit() {
    exit(0);
}

bool Board::noMove() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension-1; j++) {
            if (mBoard[i*dimension + j].value() == mBoard[i*dimension + j + 1].value()) return false;
        }

    }

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension - 1; j++) {
            if (mBoard[i + j * 4].value() == mBoard[i + (j + 1) * 4].value()) return false;
        }
    }

    return true;
}

int Board::generateRandom(std::vector<int>& candidates) {
    std::uniform_int_distribution<int> uni(0, candidates.size() - 1);
    auto random_integer = uni(rng);

    return candidates[random_integer];
}



bool Board::noFreeCells() {
    std::vector<int> freeCells;
    for (int i = 0; i < mBoard.size(); i++) {
        if (mBoard[i].isFree()) freeCells.push_back(i);
    }
    return (freeCells.size() == 0);
}
void Board::newCell(int val) {

    std::vector<int> freeCells;
    for (int i = 0; i < mBoard.size(); i++) {
        if (mBoard[i].isFree()) freeCells.push_back(i);
    }

    if (noFreeCells() && !noMove()) return;

    int mIndex = generateRandom(freeCells);
    mBoard[mIndex].setValue(val);
}


int Board::choose() {

        char c;
#ifdef _WIN32
        while (c = _getch()) {
            if (c == KEY_LEFT) return LEFT;
            if (c == 'q') return QUIT;
            if (c == KEY_RIGHT)return RIGHT;
            if (c == KEY_UP)return UP;
            if (c == KEY_DOWN)return DOWN;

#elif defined __unix__
        char d, e;
        enableRawMode();
        while (std::cin >> c) {
            if (c == 'q')return QUIT;
            std::cin >> d >> e;
            if ((c == 27) && (d == 91)) {
                if (e == 65)return UP;
                if (e == 66)return DOWN;
                if (e == 67)return RIGHT;
                if (e == 68)return LEFT;
            }
#endif

        }
}

void Board::drawBoard() {
#ifdef __unix__
    system("clear");
#elif defined _WIN32
    system("cls");
#endif
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "\tscore:       " << score << "\n";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "\t";
    for (int i = 0; i < dimension; i++)
        std::cout << mBoard[i].value() << "    ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "\t";
    for (int i = dimension; i < dimension * 2; i++)
        std::cout << mBoard[i].value() << "    ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "\t";
    for (int i = dimension * 2; i < dimension * 3; i++)
        std::cout << mBoard[i].value() << "    ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "\t";
    for (int i = dimension * 3; i < dimension * 4; i++)
        std::cout << mBoard[i].value() << "    ";

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

void Board::play() {
    drawBoard();
    getChoice(choose());
}
