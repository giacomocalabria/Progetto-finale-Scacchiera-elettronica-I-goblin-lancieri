// Author: NICOLA MARITAN

#include "pawn.h"
#include "board.h"
#include <algorithm>

using namespace std;

/*
    Costruttore della classe pawn. Essa semplicemente richiama il
    costruttore della base class piece.
*/
//pawn::pawn(const position& _pos, int _player, board* _running_board) : piece(_pos, _player, _running_board)
pawn::pawn(const position& _pos, int _player) : piece(_pos, _player) {}



bool pawn::can_move_to(const position& dest, const vector<piece*>& board_pieces)
{
    if (!is_valid_position_8(dest))
        return false;

    vector<position> possible_positions = get_possible_positions();
    vector<position>::iterator it;
    it = find(possible_positions.begin(), possible_positions.end(), dest);
    if (it == possible_positions.end())
        return false;

    int sign = player == board::PLAYER_1 ? -1 : 1;  // orientazione
    if (dest == pos + (sign * position(1, 0)))
    {
        // Allora si sta muovendo in avanti
        if (board_pieces[make_index_8(dest)])
        {
            return false;
        }
        is_init_pos = false;
        return true;
    }

    if (dest == pos + (sign * position(2, 0)))
    {
        // Allora si sta muovendo in avanti
        if (board_pieces[make_index_8(dest)] || board_pieces[make_index_8(dest.row - sign, dest.col)])
        {
            return false;
        }
        is_init_pos = false;
        return true;
    }

    // Sicuramente si sta muovendo in diagonale (gli altri casi hanno già portato a conclusione)

    piece* other = board_pieces[make_index_8(dest)];
    if (other)
    {
        if (player != other->get_player())
        {
            is_init_pos = false;
            return true;
        }
    }
    return false;
}

inline char pawn::symbol()
{
    /*if (player == board::PLAYER_1)    // Player 1
        return 'p';
    return 'P'; // Player 2*/

    return player == board::PLAYER_1 ? 'p' : 'P';
}

std::vector<position> pawn::get_possible_positions()
{
    std::vector<position> possible_positions;
    int sign = player == board::PLAYER_1 ? -1 : 1;  // orientazione
    if (is_init_pos)
    {
        possible_positions.push_back(pos + (sign * position(2, 0)));
    }
    possible_positions.push_back(pos + (sign * position(1, 0)));    // avanza di una casa in verticale
    possible_positions.push_back(pos + (sign * position(1, 1)));    // avanza di una casa in verticale e orizzontale
    possible_positions.push_back(pos + (sign * position(1, -1)));   

    return possible_positions;
}

