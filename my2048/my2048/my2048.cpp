#include <iostream>
#include <stdlib.h>
#include <vector>
#include <thread>
#include <chrono>
#include <random>

#ifdef _WIN32
#include <conio.h>
#endif // 
#ifdef __unix__
#include <unistd.h>
#include <termios.h>
#endif


#ifdef _WIN32
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#endif

int score = 0;
bool moved = false;

std::random_device rd;
std::mt19937 rng(rd());

int randVal();
void newCell(int);
void gameOver();
const unsigned int dimension = 4;


class Cell{
	public:
        Cell();
        ~Cell();
		int value()const{return mValue;}
        void setValue(int val);
        bool isFree() const;
        void setFree(bool);
	private:
		int mValue;
        bool mFree;
};

Cell::Cell() :
    mValue{ 0 },
    mFree{ true }
{
}


Cell::~Cell(){}

bool Cell::isFree() const { return mFree; }
void Cell::setFree(bool f) { mFree = f; }

void Cell::setValue(int val) {
    mValue = val;
    if (val> 0) mFree = false;
    if (val == 0) mFree = true;
}

std::vector<Cell> board;

bool noMove(std::vector<Cell>&);
bool noMove(std::vector<Cell>&);
bool noFreeCells(std::vector<Cell>&);

void display(){
#ifdef __unix__
		system("clear");
#endif
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "\tscore:       " << score << "\n";
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "\t";
		for (int i = 0; i < dimension ;i++)
			std::cout << board[i].value() << "    ";
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "\t";
        for (int i = dimension; i < dimension*2; i++)
			std::cout << board[i].value() << "    ";
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "\t";
        for (int i = dimension*2; i < dimension*3; i++)
			std::cout << board[i].value() << "    ";
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "\t";
        for (int i = dimension*3; i < dimension*4; i++)
			std::cout << board[i].value() << "    ";

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;




}


void compressLeft() {
    for (int x = 0; x < dimension;  x++) {
        for (int i = 0; i < dimension; i++) {
            if (board[x*dimension+i].value() == 0) {
                for (int j = i + 1; j < dimension; j++) {
                    if (board[x*dimension+j].value() > 0) {
                        board[x*dimension+i].setValue(board[x*dimension+j].value());
                        board[x*dimension+j].setValue(0);
                        moved = true;
                        break;
                    }
                }
            }
        }
    }
}

void joinLeft() {
    for (int x = 0; x < dimension;  x++) {
        for (int i = 0; i < dimension-1; i++) {
                    if (board[x*dimension+i].value() == board[x*dimension+i+1].value() && board[x*dimension+i].value() != 0) {
                        board[x*dimension+i].setValue(board[x*dimension+i].value()*2);
                        score += board[x*dimension + i].value();
                        board[x*dimension+i+1].setValue(0);
                        moved = true;
                    }
        }
    }

}

void compressUp() {
    for (int x = 0; x < dimension;  x++) {
        for (int i = 0; i < dimension; i++) {
            if (board[x+i*dimension].value() == 0) {
                for (int j = i + 1; j < dimension; j++) {
                    if (board[x+j*dimension].value() > 0) {
                        board[x+i*dimension].setValue(board[x+j*dimension].value());
                        board[x+j*dimension].setValue(0);
                        moved = true;
                        break;
                    }
                }
            }
        }
    }
}

void joinUp() {
    for (int x = 0; x < dimension;  x++) {
        for (int i = 0; i < dimension-1; i++) {
            if (board[x+i*dimension].value() == board[x+(i+1)*dimension].value() && board[x+i*dimension].value() != 0) {
                        board[x+i*dimension].setValue(board[x+(i+1)*dimension].value()*2);
                        score += board[x + i * dimension].value();
                        board[x+(i+1)*dimension].setValue(0);
                        moved = true;
            }
        }
    }

}

void compressRight() {
    for (int x = 0; x < dimension; x++) {
        for (int i = dimension - 1; i > 0; i--) {
            if (board[x*dimension+i].value() == 0) {
                for (int j = i - 1; j >= 0; j--) {
                    if (board[x*dimension+j].value() > 0) {
                        board[x*dimension+i].setValue(board[x*dimension+j].value());
                        board[x*dimension+j].setValue(0);
                        moved = true;
                        break;
                    }
                }
            }
        }
    }
}

void joinRight() {
    for (int x = 0; x < dimension; x++) {
        for (int i = dimension - 1; i > 0; i--) {
            if (board[x*dimension+i].value() == board[x*dimension+i-1].value() && board[x*dimension+i].value() != 0) {
                board[x*dimension+i].setValue(board[x*dimension+i-1].value()*2);
                score += board[x*dimension + i].value();
                board[x*dimension+i-1].setValue(0);
                moved = true;
            }
        }
    }

}

void compressDown() {
    for (int x = 0; x < dimension; x++) {
        for (int i = dimension - 1; i > 0; i--) {
            if (board[x+i*dimension].value() == 0) {
                for (int j = i - 1; j >= 0; j--) {
                    if (board[x+j*dimension].value() > 0) {
                        board[x+i*dimension].setValue(board[x+j*dimension].value());
                        board[x+j*dimension].setValue(0);
                        moved = true;
                        break;
                    }
                }
            }
        }
    }
}

void joinDown() {
    for (int x = 0; x < dimension; x++) {
        for (int i = dimension - 1; i > 0; i--) {
            if (board[x+i*dimension].value() == board[x+(i-1)*dimension].value() && board[x+i*dimension].value() != 0) {
                board[x+i*dimension].setValue(board[x+(i-1)*dimension].value()*2);
                score += board[x + i * dimension].value();
                board[x+(i-1)*dimension].setValue(0);
                moved = true;
            }
        }
    }

}

void left()
{
    compressLeft();
    joinLeft();
    compressLeft();
#ifdef _WIN32
    system("cls");
#elif defined __unix__
    system("clear");
#endif // 

    if (moved) {
        newCell(randVal());
        moved = false;
    }

    if (noMove(board) && noFreeCells(board)) gameOver();

    display();
}

void right()
{
    compressRight();
    joinRight();
    compressRight();
#ifdef _WIN32
    system("cls");
#elif defined __unix__
    system("clear");
#endif // 
    if (moved) {
        newCell(randVal());
        moved = false;
    }

    if (noMove(board) && noFreeCells(board)) gameOver();

    display();
}

void up() {
    compressUp();
    joinUp();
    compressUp();

#ifdef _WIN32
    system("cls");
#elif defined __unix__
    system("clear");
#endif // 

    if (moved) {
        newCell(randVal());
        moved = false;
    }

    if (noMove(board) && noFreeCells(board)) gameOver();

    display();
}

void down() {
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
    
    if (noMove(board) && noFreeCells(board)) gameOver();

    display();
}

void initBoard() {
    for (int i = 0; i < 16; i++) {
        Cell cell;
        board.push_back(cell);
    }
    newCell(2);
    newCell(2);
}


#ifdef __unix__
struct termios orig_termios;
void disableRawMode(){
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode(){
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode);

	struct termios raw = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

#endif

void choose(){
	char c;
#ifdef _WIN32
    while(c = _getch()){
	    if(c == KEY_LEFT) left();
	    if(c == 'q') exit(0);
	    if (c == KEY_RIGHT) right();
	    if (c == KEY_UP) up();
	    if (c == KEY_DOWN) down();

#elif defined __unix__
	    char d,e;
	    enableRawMode();
	while(std::cin >> c){
		if (c == 'q') exit(0);
		std::cin >> d >> e;
		if((c==27) && (d == 91)){
			if (e == 65) up();
			if (e == 66) down();
			if (e == 67) right();
			if (e == 68) left();
		}
#endif

	}
}

void gameOver() {
#ifdef _WIN32
    system("cls");
#elif defined __unix__
    system("clear");
#endif
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "                    GAME OVER !!!!               ";
    std::cin.get();
    exit(0);
}

bool noMove(std::vector<Cell>& bord) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension-1; j++) {
            if (bord[i*dimension + j].value() == bord[i*dimension + j + 1].value()) return false;
        }

    }

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension - 1; j++) {
            if (bord[i + j * 4].value() == bord[i + (j + 1) * 4].value()) return false;
        }
    }

    return true;
}

int generateRandom(std::vector<int>& candidates) {
    std::uniform_int_distribution<int> uni(0, candidates.size() - 1);
    auto random_integer = uni(rng);

    return candidates[random_integer];
}

int randVal() {
    std::vector<int> numbersToChooseFrom;
    for (int i = 0; i < 20; i++) {
        if (i == 4) numbersToChooseFrom.push_back(i);
        if (i != 4) numbersToChooseFrom.push_back(2);
    }

    std::uniform_int_distribution<int> uni(0, numbersToChooseFrom.size()-1);
    auto random_integer = uni(rng);

    return numbersToChooseFrom[random_integer];


}

bool noFreeCells(std::vector<Cell>& bord) {
    std::vector<int> freeCells;
    for (int i = 0; i < bord.size(); i++) {
        if (bord[i].isFree()) freeCells.push_back(i);
    }
    return (freeCells.size() == 0);
}
void newCell(int val) {

    std::vector<int> freeCells;
    for (int i = 0; i < board.size(); i++) {
        if (board[i].isFree()) freeCells.push_back(i);
    }

    if (noFreeCells(board) && !noMove(board)) return;

    int mIndex = generateRandom(freeCells);
    board[mIndex].setValue(val);
}

int main()
{

    initBoard();
    display();
    choose();
}


