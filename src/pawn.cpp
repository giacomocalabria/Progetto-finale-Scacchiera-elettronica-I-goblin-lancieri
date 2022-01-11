// Author: EDDIE CARRARO

#include "pawn.h"

#include <algorithm>

#include "board.h"

using namespace std;

/*
    Costruttore della classe pawn. Essa semplicemente richiama il
    costruttore della base class piece. Ciò avviene in modo totalmente
    analogo nelle altre classi derivate da piece.
*/
pawn::pawn(const position& _pos, player_id _player) : piece(_pos, _player) {}

bool pawn::can_move_to(const position& dest, const vector<piece*>& board_pieces)
{
    if (!is_valid_position_8(dest))
        return false;

    can_be_passed = false;

    vector<position> possible_positions = get_possible_positions();
    vector<position>::iterator it;
    it = find(possible_positions.begin(), possible_positions.end(), dest);
    if (it == possible_positions.end())
        return false;

    int sign = player == player_id::player_1 ? -1 : 1;  // orientazione
    if (dest == pos + (sign * position(1, 0)))
    {
        // Allora si sta muovendo in avanti
        if (board_pieces[make_index_8(dest)])
        {
            return false;
        }
        is_init_pos = false;
        can_be_passed = false;
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
        can_be_passed = true;
        //ci arriva
        return true;
    }

    // Sicuramente si sta muovendo in diagonale (gli altri casi hanno già portato a conclusione)
    piece* other = board_pieces[make_index_8(dest)];
    if (other)
    {
        if (player != other->get_player())
        {
            is_init_pos = false;
            can_be_passed = false;
            return true;
        }
    }
    return false;
}

bool pawn::can_capture(const position& dest, const vector<piece*>& board_pieces)   //serve per definire la condizione di scacco del re avversario
{
    piece* other = board_pieces[make_index_8(dest)];

    // Ovviamente se nella cella di destinazione non c'è nulla non può mangiare.
    if (!other)
    {
        return false;
    }

    int sign = player == player_id::player_1 ? -1 : 1;  // orientazione

    if(other && (dest == pos + (sign * position(1, 1)) || dest == pos + (sign * position(1, -1))))
    {
        /*Se tale pedina però è dello stesso giocatore
        di questo pedone significa che non potrà mangiarlo*/
        if (other->get_player() == get_player())
            return false;

        is_init_pos = false;    //potremmo metterlo in set_position di piece.....
        can_be_passed = false;
        return true;
    }

    /*position straight_right = pos + (sign * position(1, 1));
    position straight_left = pos + (sign * position(1, 1));*/
    

    /*if (dest == pos + (sign * position(1, 1)) || dest == pos + (sign * position(1, -1)))
    {
        return true;
    }
    return false;*/

    return false;
}

inline char pawn::symbol()
{
    return player == player_id::player_1 ? 'p' : 'P';
}

/*  
    Il pawn ha come possibili posizioni principali le sue tre
    celle frontali. Se si trova nella posizione iniziale allora
    ha la possibilità di fare un salto in avanti di 2.
*/
std::vector<position> pawn::get_possible_positions()
{
    std::vector<position> possible_positions;
    int sign = player == player_id::player_1 ? -1 : 1;  // orientazione
    
    // Se si trova nella posizione iniziale
    if (is_init_pos)
    {
        possible_positions.push_back(pos + (sign * position(2, 0)));
    }

    //FARE IL RANGE CHECK DI STA ROBA !!
    possible_positions.push_back(pos + (sign * position(1, 0)));    // avanza di una casa in verticale
    possible_positions.push_back(pos + (sign * position(1, 1)));    // avanza di una casa in verticale e orizzontale
    possible_positions.push_back(pos + (sign * position(1, -1)));   

    return possible_positions;
}

