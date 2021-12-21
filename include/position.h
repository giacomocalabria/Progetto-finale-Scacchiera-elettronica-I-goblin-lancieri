#ifndef POSITION_H
#define POSITION_H

#include <iostream>

struct position
{
    position() : row{-1}, col{-1}{}
    position(int _row, int _col) : row{_row}, col{_col}{}
    position(const position& pos) : row{pos.row}, col{pos.col}{}
    int row, col;
};

position operator+(position p1, position p2);

std::ostream& operator<<(std::ostream& os, position p);

bool operator==(position p1, position p2);


#endif
