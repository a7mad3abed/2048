#include <iostream>
#include <vector>

constexpr int rowLength = 6;

class Cell {
public:
    bool isEmpty = false;
    int value() const { return mValue; }
    void setValue(int val) { mValue = val; }
private:
    int mValue = 0;
};

int main()
{

    std::vector<Cell> row(rowLength);
    row[0].setValue(4);
    row[1].setValue(8);
    row[3].setValue(8);


    for (int i = 0; i < rowLength; i++) {
        if (row[i].value() == 0) {
            for (int j = i + 1; j < rowLength;) {
                if (row[j].value() == 0)
                    continue;
                if (row[j].value() > 0) {
                    row[i].setValue(row[j].value());
                    row[j].setValue(0);
                    break;
                }
            }
        }
    }
    for (int i = 0; i < row.size(); i++)
        std::cout << row[i].value() << "  ";
    std::cin.get();
}
