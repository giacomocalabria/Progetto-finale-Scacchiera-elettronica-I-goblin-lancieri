//Nicola 

#ifndef POSITION_H
#define POSITION_H
#include <iostream>

struct Position{
    Position() : x{-1}, y{-1}{}
    Position(int _x, int _y) : x{_x}, y{_y}{}
    Position(const Position& pos) : x{pos.x}, y{pos.y}{}
    int x, y;
};

Position operator+(Position p1, Position p2);

std::ostream& operator<<(std::ostream& os, Position p);

bool operator==(Position p1, Position p2);

#endif //POSITION_H