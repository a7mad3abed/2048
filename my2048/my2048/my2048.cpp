#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#ifdef _WIN32
#include <conio.h>
#endif // 


const unsigned int rowLength = 8;

class Cell{
	public:
		int value()const{return mValue;}
		void setValue(int val){mValue = val;}
	private:
		int mValue = 0;
};

std::vector<Cell> row{rowLength};

void display(){
#ifdef __unix__
		system("clear");
#endif
		for (int i = 0; i < row.size();i++)
			std::cout << row[i].value() << "  ";
	}

void left()
{
	for (int i = 0; i < rowLength; i++){
		if(row[i].value() == 0){
			for(int j = i+1; j<rowLength;j++){
				if(row[j].value() >0){
					row[i].setValue(row[j].value());
					row[j].setValue(0);
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
		if(row[i].value() == 0){
			for(int j = i-1; j>=0;j--){
				if(row[j].value() >0){
					row[i].setValue(row[j].value());
					row[j].setValue(0);
					break;
				}
			}
		}
	}
    system("cls");
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
	row[2].setValue(4); 
	row[5].setValue(2);
	row[6].setValue(8);
	row[7].setValue(4);

    using namespace std::chrono_literals;

	std::thread view (display);
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1s);

	std::thread chos (choose);


	view.join();
	chos.join();
}


