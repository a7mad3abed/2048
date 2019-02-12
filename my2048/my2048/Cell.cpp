#include "Cell.h"

Cell::Cell() :
    mValue{ 0 },
    mFree{ true }
{
}


Cell::~Cell() {}

bool Cell::isFree() const { return mFree; }
void Cell::setFree(bool f) { mFree = f; }

void Cell::setValue(int val) {
    mValue = val;
    if (val > 0) mFree = false;
    if (val == 0) mFree = true;
}
