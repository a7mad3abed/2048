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


const unsigned int rowColLength = 4;
const unsigned int colLength = 4;
const unsigned int noOfRowsCols = 4;

class Cell{
	public:
        Cell();
        ~Cell();
		int value()const{return mValue;}
		void setValue(int val){mValue = val;}
	private:
		int mValue;
};

Cell::Cell() :
    mValue{ 0 }
{}

Cell::~Cell(){}

std::vector<Cell> board;

std::vector<std::vector<Cell>> rows(4, std::vector<Cell>(4));
std::vector<std::vector<Cell>> cols(4, std::vector<Cell>(4));

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

void flushRows() {
    for (int i = 0; i < rowColLength; i++) {
        for (int j = 0; j < rowColLength; j++) {
            board[i * rowColLength + j].setValue(rows[i][j].value());
        }
    }
}

void loadRows() {
    for (int i = 0; i < noOfRowsCols; i++) {
        for (int j = 0; j < rowColLength; j++) {
            rows[i][j].setValue(board[i * noOfRowsCols + j].value());
        }
    }
}

void loadCols() {
    for (int i = 0; i < noOfRowsCols; i++) {
        for (int j = 0; j < rowColLength; j++) {
            cols[i][j].setValue(board[i + j * 4].value());
        }

    }
}

void flushCols() {
    for (int i = 0; i < rowColLength; i++) {
        for (int j = 0; j < rowColLength; j++) {
            board[i + rowColLength * j].setValue(cols[i][j].value());
        }
    }
}

void compressLeft() {
    for (int x = 0; x < noOfRowsCols;  x++) {
        for (int i = 0; i < rowColLength; i++) {
            if (rows[x][i].value() == 0) {
                for (int j = i + 1; j < rowColLength; j++) {
                    if (rows[x][j].value() > 0) {
                        rows[x][i].setValue(rows[x][j].value());
                        rows[x][j].setValue(0);
                        break;
                    }
                }
            }
        }
    }
}

void compressUp() {
    for (int x = 0; x < noOfRowsCols;  x++) {
        for (int i = 0; i < rowColLength; i++) {
            if (cols[x][i].value() == 0) {
                for (int j = i + 1; j < rowColLength; j++) {
                    if (cols[x][j].value() > 0) {
                        cols[x][i].setValue(cols[x][j].value());
                        cols[x][j].setValue(0);
                        break;
                    }
                }
            }
        }
    }
}

void compressRight() {
    for (int x = 0; x < noOfRowsCols; x++) {
        for (int i = noOfRowsCols - 1; i > 0; i--) {
            if (rows[x][i].value() == 0) {
                for (int j = i - 1; j >= 0; j--) {
                    if (rows[x][j].value() > 0) {
                        rows[x][i].setValue(rows[x][j].value());
                        rows[x][j].setValue(0);
                        break;
                    }
                }
            }
        }
    }
}

void compressDown() {
    for (int x = 0; x < noOfRowsCols; x++) {
        for (int i = noOfRowsCols - 1; i > 0; i--) {
            if (cols[x][i].value() == 0) {
                for (int j = i - 1; j >= 0; j--) {
                    if (cols[x][j].value() > 0) {
                        cols[x][i].setValue(cols[x][j].value());
                        cols[x][j].setValue(0);
                        break;
                    }
                }
            }
        }
    }
}
void left()
{
    loadRows();
    compressLeft();
    flushRows();
#ifdef _WIN32
    system("cls");
#elif defined __unix__
    system("clear");
#endif // 


    display();
}

void right()
{
    loadRows();
    compressRight();
    flushRows();
#ifdef _WIN32
    system("cls");
#elif defined __unix__
    system("clear");
#endif // 
    display();
}

void up() {
    loadCols();
    compressUp();
    flushCols();

#ifdef _WIN32
    system("cls");
#elif defined __unix__
    system("clear");
#endif // 

    display();
}

void down() {
    loadCols();
    compressDown();
    flushCols();
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

#elif defined __unix__

	    enableRawMode();
	while(std::cin >> c){
#endif

		if(c == 'l') left();
		if(c == 'q') exit(0);
        if (c == 'r') right();
        if (c == 'u') up();
        if (c == 'd') down();
	}
}
int main()
{

    initBoard();
    initRows();
    initCols();

	board[0].setValue(4); 
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


