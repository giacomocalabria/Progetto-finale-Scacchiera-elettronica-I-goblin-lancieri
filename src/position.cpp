#include "position.h"
#include <iostream>

position operator+(position p1, position p2)
{
    position p_sum(p1.row + p2.row, p1.col + p2.col);
    return p_sum;
}

position operator-(position p1, position p2)
{
    return p1 + (-1 * p2);
}

position operator*(int scalar, position p)
{
    position p_res(scalar * p.row, scalar * p.col);
    return p_res;
}

std::ostream& operator<<(std::ostream& os, position p)
{
    return os << "(" << p.row << ", " << p.col << ")";
}

bool operator==(position p1, position p2)
{
    return p1.row == p2.row && p1.col == p2.col;
}
