#include "position.h"
#include <iostream>

position operator+(position p1, position p2)
{
    position p_sum(p1.row + p2.row, p1.col + p2.col);
    return p_sum;
}

std::ostream& operator<<(std::ostream& os, position p)
{
    return os << "(" << p.row << ", " << p.col << ")";
}

bool operator==(position p1, position p2)
{
    return p1.row == p2.row && p1.col == p2.col;
}
