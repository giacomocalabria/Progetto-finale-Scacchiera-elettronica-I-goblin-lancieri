// Author: NICOLA MARITAN

#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <string>

struct position
{
    position() : row{-1}, col{-1}{}
    position(int _row, int _col) : row{_row}, col{_col}{}
    position(const position& pos) : row{pos.row}, col{pos.col}{}
    position(std::string& pos);
    int row, col;
};

position operator+(position p1, position p2);

position operator-(position p1, position p2);

position operator*(int scalar, position p);

std::ostream& operator<<(std::ostream& os, position p);

bool operator==(position p1, position p2);

int make_index_8(position p);

int make_index_8(int row, int col);

bool is_valid_position_8(const position& pos);

constexpr int max_position {8};
constexpr int min_position {0};


#endif