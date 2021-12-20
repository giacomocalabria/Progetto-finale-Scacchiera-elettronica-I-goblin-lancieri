#include "position.h"
#include <iostream>

position operator+(position p1, position p2)
{
    position p_sum(p1.x + p2.x, p1.y + p2.y);
    return p_sum;
}

std::ostream& operator<<(std::ostream& os, position p)
{
    return os << "(" << p.x << ", " << p.y << ")";
}

bool operator==(position p1, position p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}
