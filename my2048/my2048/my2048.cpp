#include <iostream>
#include <stdlib.h>
#include <vector>
#include <thread>
#include <chrono>
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


const unsigned int rowColLength = 4;
const unsigned int colLength = 4;
const unsigned int noOfRowsCols = 4;

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
    if (mValue > 0) mFree = false;
    if (mValue == 0) mFree = true;
}

std::vector<Cell> board;


void display(){
#ifdef __unix__
		system("clear");
#endif
		for (int i = 0; i < rowColLength ;i++)
			std::cout << board[i].value() << "    ";
        std::cout << std::endl;
        std::cout << std::endl;
        for (int i = rowColLength; i < rowColLength*2; i++)
			std::cout << board[i].value() << "    ";
        std::cout << std::endl;
        std::cout << std::endl;
        for (int i = rowColLength*2; i < rowColLength*3; i++)
			std::cout << board[i].value() << "    ";
        std::cout << std::endl;
        std::cout << std::endl;
        for (int i = rowColLength*3; i < rowColLength*4; i++)
			std::cout << board[i].value() << "    ";

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;


}


void compressLeft() {
    for (int x = 0; x < noOfRowsCols;  x++) {
        for (int i = 0; i < rowColLength; i++) {
            if (board[x*4+i].value() == 0) {
                for (int j = i + 1; j < rowColLength; j++) {
                    if (board[x*4+j].value() > 0) {
                        board[x*4+i].setValue(board[x*4+j].value());
                        board[x*4+j].setValue(0);
                        break;
                    }
                }
            }
        }
    }
}

void joinLeft() {
    for (int x = 0; x < noOfRowsCols;  x++) {
        for (int i = 0; i < rowColLength-1; i++) {
                    if (board[x*4+i].value() == board[x*4+i+1].value()) {
                        board[x*4+i].setValue(board[x*4+i].value()*2);
                        board[x*4+i+1].setValue(0);
                    }
        }
    }

}

void compressUp() {
    for (int x = 0; x < noOfRowsCols;  x++) {
        for (int i = 0; i < rowColLength; i++) {
            if (board[x+i*4].value() == 0) {
                for (int j = i + 1; j < rowColLength; j++) {
                    if (board[x+j*4].value() > 0) {
                        board[x+i*4].setValue(board[x+j*4].value());
                        board[x+j*4].setValue(0);
                        break;
                    }
                }
            }
        }
    }
}

void joinUp() {
    for (int x = 0; x < noOfRowsCols;  x++) {
        for (int i = 0; i < rowColLength-1; i++) {
            if (board[x+i*4].value() == board[x+(i+1)*4].value()) {
                        board[x+i*4].setValue(board[x+(i+1)*4].value()*2);
                        board[x+(i+1)*4].setValue(0);
            }
        }
    }

}

void compressRight() {
    for (int x = 0; x < noOfRowsCols; x++) {
        for (int i = noOfRowsCols - 1; i > 0; i--) {
            if (board[x*4+i].value() == 0) {
                for (int j = i - 1; j >= 0; j--) {
                    if (board[x*4+j].value() > 0) {
                        board[x*4+i].setValue(board[x*4+j].value());
                        board[x*4+j].setValue(0);
                        break;
                    }
                }
            }
        }
    }
}

void joinRight() {
    for (int x = 0; x < noOfRowsCols; x++) {
        for (int i = noOfRowsCols - 1; i > 0; i--) {
            if (board[x*4+i].value() == board[x*4+i-1].value()) {
                board[x*4+i].setValue(board[x*4+i-1].value()*2);
                board[x*4+i-1].setValue(0);
            }
        }
    }

}

void compressDown() {
    for (int x = 0; x < noOfRowsCols; x++) {
        for (int i = noOfRowsCols - 1; i > 0; i--) {
            if (board[x+i*4].value() == 0) {
                for (int j = i - 1; j >= 0; j--) {
                    if (board[x+j*4].value() > 0) {
                        board[x+i*4].setValue(board[x+j*4].value());
                        board[x+j*4].setValue(0);
                        break;
                    }
                }
            }
        }
    }
}

void joinDown() {
    for (int x = 0; x < noOfRowsCols; x++) {
        for (int i = noOfRowsCols - 1; i > 0; i--) {
            if (board[x+i*4].value() == board[x+(i-1)*4].value()) {
                board[x+i*4].setValue(board[x+(i-1)*4].value()*2);
                board[x+(i-1)*4].setValue(0);
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
    display();
}

void initBoard() {
    for (int i = 0; i < 16; i++) {
        Cell cell;
        board.push_back(cell);
    }
}

void initRows() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            Cell cell;
            rows[i].push_back(cell);
        }
    }
}

void initCols() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            Cell cell;
            cols[i].push_back(cell);
        }
    }
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
int main()
{

    initBoard();

    board[0].setValue(2);
	board[2].setValue(2);
	board[3].setValue(4);
    board[6].setValue(8);
    board[11].setValue(2);
    board[13].setValue(2);

    using namespace std::chrono_literals;

	std::thread view (display);
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1s);

	std::thread chos (choose);


	view.join();
	chos.join();
}


