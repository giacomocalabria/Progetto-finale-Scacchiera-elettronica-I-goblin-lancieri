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

int make_index_8(position p)
{
    constexpr int pos_max{8};
    return p.row * pos_max + p.col;
}

int make_index_8(int row, int col)
{
    return make_index_8(position(row, col));
}

bool is_valid_position_8(const position& pos)
{
    //constexpr int pos_max{8};

    return pos.row < max_position && pos.col < max_position && pos.row >= min_position && pos.col >= min_position;
}
