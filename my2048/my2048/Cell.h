#ifndef _Cell_h
#define _Cell_h



class Cell {
public:
    Cell();
    ~Cell();
    int value()const { return mValue; }
    void setValue(int val);
    bool isFree() const;
    void setFree(bool);
private:
    int mValue;
    bool mFree;
}; 

#endif
