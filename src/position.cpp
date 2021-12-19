//Nicola

#include "Position.h"
#include <iostream>

Position operator+(Position p1, Position p2)
{
    //std::cout << p1.x << " " << p2.x << std::endl;
    //std::cout << p1.y << " " << p2.y << std::endl;
    Position p_sum(p1.x + p2.x, p1.y + p2.y);
    return p_sum;
}

std::ostream& operator<<(std::ostream& os, Position p)
{
    return os << "(" << p.x << ", " << p.y << ")";
}

bool operator==(Position p1, Position p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

//void f(){std::cout << "f called" << std::endl;}