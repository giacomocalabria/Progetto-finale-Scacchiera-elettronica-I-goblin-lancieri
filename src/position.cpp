#include "position.h"

#include <iostream>
#include <string>

position::position(const std::string& pos){
    char c_col = pos.at(0);
    char c_row = pos.at(1);
    if(c_col < 'a') //lettera maiuscola
        col = c_col - 'A';
    else            //lettera minuscola
        col = c_col - 'a';
    row = c_row - '0';
}

position operator+(position p1, position p2)
{
    /*position p_sum(p1.row + p2.row, p1.col + p2.col);
    return p_sum;*/
    return position(p1.row + p2.row, p1.col + p2.col);
}

position operator-(position p1, position p2)
{
    return p1 + (-1 * p2);
}

position operator*(int scalar, position p)
{
    /*position p_res(scalar * p.row, scalar * p.col);
    return p_res;*/
    return position(scalar * p.row, scalar * p.col);
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
    return p.row * max_position + p.col;
}

int make_index_8(int row, int col)
{
    return make_index_8(position(row, col));
}

bool is_valid_position_8(const position& pos)
{
    return pos.row < max_position && pos.col < max_position && pos.row >= min_position && pos.col >= min_position;
}

std::string get_string(const position& pos){
    std::string s;
    s.push_back((char) (pos.col + 'A'));
    s.push_back((char) (pos.row + '0'));
    return s;
}
