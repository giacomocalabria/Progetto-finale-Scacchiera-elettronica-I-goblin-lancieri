// Author: NICOLA MARITAN

#include "position.h"

#include <iostream>
#include <string>

position::position(const std::string& pos)
{
    char c_col = pos.at(0);
    char c_row = pos.at(1);
    if(c_col < 'a') //lettera maiuscola
        col = c_col - 'A';
    else            //lettera minuscola
        col = c_col - 'a';
    row = '8' - c_row;
}

position operator+(position p1, position p2)
{
    return position(p1.row + p2.row, p1.col + p2.col);
}

position operator-(position p1, position p2)
{
    return p1 + (-1 * p2);
}

position operator*(int scalar, position p)
{
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

position position_from_8(int idx)
{
    return position(idx/8, idx - (idx/8)*8);    //idx/8 mi da un int, troncandomi il resto e trovando la riga corrispondente
}

bool is_valid_position_8(const position& pos)
{
    return pos.row < max_position && pos.col < max_position && pos.row >= min_position && pos.col >= min_position;
}

std::string get_string_8(const position& pos)
{
    if (!is_valid_position_8(pos))
    {
        throw bad_position_8();
    }
    std::string s;
    s.push_back((char) (pos.col + 'A'));
    s.push_back((char) (pos.row + '1'));
    return s;
}

std::string get_string_move_8(const position& p1, const position& p2)
{
    if (!is_valid_position_8(p1) || !is_valid_position_8(p2))
    {
        throw bad_position_8();
    }

    char p1_row = '8' - p1.row;
    char p1_col = 'A' + p1.col;
    char p2_row = '8' - p2.row;
    char p2_col = 'A' + p2.col;

    std::string str{p1_col, p1_row, ' ', p2_col, p2_row};
    return str;
}
