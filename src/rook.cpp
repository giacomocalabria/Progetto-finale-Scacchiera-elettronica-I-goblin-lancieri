// Author: NICOLA MARITAN

#include "rook.h"
#include "board.h"
#include <algorithm>

using namespace std;


bool rook::can_move_to(const position& dest, piece* const mat[][piece::max_position])
{
    vector<position> possible_positions = get_possible_positions();
    vector<position>::iterator it;
    it = find(possible_positions.begin(), possible_positions.end(), dest);
    if (it == possible_positions.end())
        return false;

    position cursor = pos;
    piece* other;
    
    // ----------- scansione in basso -----------
    if (dest.row > pos.row)
    {
        while (cursor.row < piece::max_position && cursor.row < dest.row)
        {
            cursor = pos + position(1, 0);
            other = mat[cursor.row][cursor.col];
            if (other)
                return false;
        }
    }
    // ----------- scansione in alto -----------
    else if (dest.row < pos.row)
    {
        while (cursor.row >= piece::min_position && cursor.row > dest.row)
        {
            cursor = pos - position(1, 0);
            other = mat[cursor.row][cursor.col];
            if (other)
                return false;
        }
    }
    // ----------- scansione a destra -----------
    else if (dest.col > pos.col)
    {
        while (cursor.col < piece::max_position && cursor.col < dest.col)
        {   
            cursor = pos + position(0, 1);
            other = mat[cursor.row][cursor.col];
            if (other)
                return false;
        }
    }
    // ----------- scansione a sinistra -----------
    else if (dest.col < pos.col)
    {
        while (cursor.col >= piece::min_position && cursor.col > dest.col)
        {
            cursor = pos - position(0, 1);
            other = mat[cursor.row][cursor.col];
            if (other)
                return false;
        }
    }

    // se la cella di arrivo è occupata ed è occupata da un pezzo del stesso giocatore -> rest falso
    if (other && other->get_player() == player)
    {
        return false;
    }
    return true;
}

inline char rook::symbol()
{
    return player == board::PLAYER_1 ? 't' : 'T';
}

std::vector<position> rook::get_possible_positions()
{
    std::vector<position> possible_positions;

    position cursor = pos;

    // ----------- scansione a destra -----------
    cursor = pos;
    while (cursor.col <= piece::max_position)
    {
        cursor = pos + position(0, 1);
        possible_positions.push_back(cursor);
    }

    // ----------- scansione a sinistra -----------
    cursor = pos;
    while (cursor.col >= piece::min_position)
    {
        cursor = pos - position(0, 1);
        possible_positions.push_back(cursor);
    }

    // ----------- scansione a sinistra -----------
    cursor = pos;
    while (cursor.col <= piece::max_position)
    {
        cursor = pos + position(1, 0);
        possible_positions.push_back(cursor);
    }

    // ----------- scansione a sinistra -----------
    cursor = pos;
    while (cursor.col >= piece::min_position)
    {
        cursor = pos - position(1, 0);
        possible_positions.push_back(cursor);
    }

    return possible_positions;
}

