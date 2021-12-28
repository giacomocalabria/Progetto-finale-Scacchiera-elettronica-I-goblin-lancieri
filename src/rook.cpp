// Author: NICOLA MARITAN

#include "rook.h"
#include "board.h"
#include <algorithm>

using namespace std;


bool rook::can_move_to(const position& dest, const vector<piece*>& board_pieces)
{
    vector<position> possible_positions = get_possible_positions();
    //std::cout << "Positions generated (Rook).\n";
    vector<position>::iterator it;
    it = find(possible_positions.begin(), possible_positions.end(), dest);
    if (it == possible_positions.end())
        return false;

    //std::cout << "Destination in possible_positions.\n";
    position cursor = pos;
    piece* other;
    
    // ----------- scansione in basso -----------  
    if (dest.row > pos.row)
    {
        //std::cout << "Scansione in basso.\n";
        cursor = cursor + position(1, 0);
        while (cursor.row < piece::max_position && cursor.row < dest.row)
        {
            other = board_pieces[make_index_8(cursor)];
            if (other)
                return false;
            cursor = cursor + position(1, 0);
        }
    }
    // ----------- scansione in alto -----------
    else if (dest.row < pos.row)
    {
        //std::cout << "Scansione in alto.\n";
        cursor = cursor - position(1, 0);
        while (cursor.row >= piece::min_position && cursor.row > dest.row)
        {
            other = board_pieces[make_index_8(cursor)];
            if (other)
            {
                //cout << "Obstacle.\n";
                return false;
            }
            cursor = cursor - position(1, 0);
        }
    }
    // ----------- scansione a destra -----------
    else if (dest.col > pos.col)
    {
        //std::cout << "Scansione a destra.\n";
        cursor = cursor + position(0, 1);
        while (cursor.col < piece::max_position && cursor.col < dest.col)
        {    
            other = board_pieces[make_index_8(cursor)];
            if (other)
                return false;
            cursor = cursor + position(0, 1);
        }
    }
    // ----------- scansione a sinistra -----------
    else if (dest.col < pos.col)
    {
        //std::cout << "Scansione a sinistra.\n";
        cursor = cursor - position(0, 1);
        while (cursor.col >= piece::min_position && cursor.col > dest.col)
        {
            other = board_pieces[make_index_8(cursor)];
            if (other)
                return false;
            cursor = cursor - position(0, 1);
        }
    }

    // se la cella di arrivo è occupata ed è occupata da un pezzo del stesso giocatore -> rest falso
    other = board_pieces[make_index_8(dest)];
    //cout << other->symbol();
    if (other && other->get_player() == player)
    {
        //cout << "Same color.\n";
        return false;
    }
    return true;
}

bool rook::can_eat(const position& dest, const vector<piece*>& board_pieces)
{
    return this->can_move_to(dest, board_pieces);
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
    //std::cout << "Scansione a destra.\n";
    cursor = pos;
    while (cursor.col < piece::max_position)
    {
        cursor = cursor + position(0, 1);
        possible_positions.push_back(cursor);
    }

    // ----------- scansione a sinistra -----------
    //std::cout << "Scansione a sinistra.\n";
    cursor = pos;
    while (cursor.col > piece::min_position)
    {
        cursor = cursor - position(0, 1);
        possible_positions.push_back(cursor);
    }

    // ----------- scansione in basso -----------
    //std::cout << "Scansione in basso.\n";
    cursor = pos;
    while (cursor.row < piece::max_position)
    {
        cursor = cursor + position(1, 0);
        possible_positions.push_back(cursor);
    }

    // ----------- scansione in alto -----------
    //std::cout << "Scansione in alto.\n";
    cursor = pos;
    while (cursor.row > piece::min_position)
    {
        cursor = cursor - position(1, 0);
        possible_positions.push_back(cursor);
    }

    return possible_positions;
}

