// Author: EDDIE CARRARO

#include "position.h"

#include <iostream>
#include <string>

using namespace std;

position::position(const string& pos)
{
    char c_col = pos.at(0);
    char c_row = pos.at(1);
    constexpr char min_col_lowercase {'a'};

    if(c_col < min_col_lowercase) //lettera maiuscola
        col = c_col - min_col;
    else                          //lettera minuscola
        col = c_col - min_col_lowercase;
    row = max_row - c_row;
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

ostream& operator<<(ostream& os, position p)
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
    //idx/8 mi da un int, troncandomi il resto e trovando la riga corrispondente
    return position(idx / 8, idx - (idx / 8) * 8);
}

bool is_valid_position_8(const position& pos)
{
    // Una posizione e' valida se ha riga e colonne comprese fra 0 e 7 inclusi
    return pos.row < max_position && pos.col < max_position && pos.row >= min_position && pos.col >= min_position;
}

string get_string_8(const position& pos)
{
    if (!is_valid_position_8(pos))
    {
        throw bad_position_8();
    }
    string s;
    s.push_back((char) (pos.col + min_col));
    s.push_back((char) max_row - pos.row);
    return s;
}

string get_string_move_8(const position& p1, const position& p2)
{
    if (!is_valid_position_8(p1) || !is_valid_position_8(p2))
    {
        throw bad_position_8();
    }

    char p1_row = max_row - p1.row;
    char p1_col = min_col + p1.col;
    char p2_row = max_row - p2.row;
    char p2_col = min_col + p2.col;

    string str{p1_col, p1_row, ' ', p2_col, p2_row};
    return str;
}
