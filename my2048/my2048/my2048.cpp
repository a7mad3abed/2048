#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

const unsigned int rowLength = 8;

class Cell{
	public:
		int value()const{return mValue;}
		void setValue(int val){mValue = val;}
	private:
		int mValue = 0;
};

std::vector<Cell> row{rowLength};


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
}
void display(){
	while(1){
#ifdef __unix__
		system("clear");
#endif
		for (int i = 0; i < row.size();i++)
			std::cout << row[i].value() << "  ";
		std::cout << std::endl;
	}

}
void choose(){
	char c;
	while(std::cin >> c){
		if(c == 'r') left();
		if(c == 'q') exit(0);
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
    std::this_thread::sleep_for(5s);

	std::thread chos (choose);

	view.join();
	chos.join();
}


