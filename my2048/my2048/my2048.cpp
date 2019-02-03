#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#ifdef _WIN32
#include <conio.h>
#endif // 


const unsigned int rowLength = 4;

class Cell{
	public:
		int value()const{return mValue;}
		void setValue(int val){mValue = val;}
	private:
		int mValue = 0;
};

std::vector<Cell> board{16};

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

void left()
{
	for (int i = 0; i < rowLength; i++){
		if(board[i].value() == 0){
			for(int j = i+1; j<rowLength;j++){
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
	board[0].setValue(4); 
	board[2].setValue(2);
	board[3].setValue(4);

    using namespace std::chrono_literals;

	std::thread view (display);
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1s);

	std::thread chos (choose);


	view.join();
	chos.join();
}


