#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#ifdef _WIN32
#include <conio.h>
#endif // 


const unsigned int rowLength = 4;
const unsigned int colLength = 4;

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

void display(){
#ifdef __unix__
		system("clear");
#endif
		for (int i = 0; i < rowLength;i++)
			std::cout << board[i].value() << "  ";
        std::cout << std::endl;
        for (int i = rowLength; i < rowLength*2; i++)
			std::cout << board[i].value() << "  ";
        std::cout << std::endl;
        for (int i = rowLength*2; i < rowLength*3; i++)
			std::cout << board[i].value() << "  ";
        std::cout << std::endl;
        for (int i = rowLength*3; i < rowLength*4; i++)
			std::cout << board[i].value() << "  ";

}

void flushRow() {
    for (int i = 0; i < rows.size(); i++) {
        for (int j = 0; j < rows[i].size(); j++) {
            board[i * 4 + j].setValue(rows[i][j].value());
        }
    }
}

void loadRows() {
    for (int i = 0; i < rows.size(); i++) {
        for (int j = 0; j < rows[i].size(); j++) {
            rows[i][j].setValue(board[i * 4 + j].value());
        }
    }
}

void left()
{
    for (int x = 0; x < rows.size(); x++) {
        for (int i = 0; i < rowLength; i++) {
            if (rows[x][i].value() == 0) {
                for (int j = i + 1; j < rowLength; j++) {
                    if (rows[x][j].value() > 0) {
                        rows[x][i].setValue(rows[x][j].value());
                        rows[x][j].setValue(0);
                        break;
                    }
                }
            }
        }
    }
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
void right()
{
	for (int i = rowLength-1; i >= 0; i--){
		if(board[i].value() == 0){
			for(int j = i-1; j>=0;j--){
				if(board[j].value() >0){
					board[i].setValue(board[j].value());
					board[j].setValue(0);
					break;
				}
			}
		}
	}
#ifdef _WIN32
    system("cls");
#elif defined __unix__
    system("clear");
#endif // 
    display();
}

void choose(){
	char c;
#ifdef _WIN32
    while(c = _getch()){

#elif defined __unix__
	while(std::cin >> c){
#endif

		if(c == 'l') left();
		if(c == 'q') exit(0);
        if (c == 'r') right();
	}
}
int main()
{

    initBoard();
    initRows();

	board[0].setValue(4); 
	board[2].setValue(2);
	board[3].setValue(4);
    board[6].setValue(8);

    using namespace std::chrono_literals;

	std::thread view (display);
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1s);

	std::thread chos (choose);


	view.join();
	chos.join();
}


