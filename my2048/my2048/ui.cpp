#include "ui.h"
#include "Board.h"

void display(std::vector<Cell> board) {
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
        std::cout << board[i].value() << "    ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "\t";
    for (int i = dimension; i < dimension * 2; i++)
        std::cout << board[i].value() << "    ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "\t";
    for (int i = dimension * 2; i < dimension * 3; i++)
        std::cout << board[i].value() << "    ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "\t";
    for (int i = dimension * 3; i < dimension * 4; i++)
        std::cout << board[i].value() << "    ";

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

}
