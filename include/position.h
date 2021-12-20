#ifndef POSITION_H
#define POSITION_H

#include <iostream>

struct position
{
    position() : x{-1}, y{-1}{}
    position(int _x, int _y) : x{_x}, y{_y}{}
    position(const position& pos) : x{pos.x}, y{pos.y}{}
    int x, y;
};

position operator+(position p1, position p2);

std::ostream& operator<<(std::ostream& os, position p);

bool operator==(position p1, position p2);


#endif
