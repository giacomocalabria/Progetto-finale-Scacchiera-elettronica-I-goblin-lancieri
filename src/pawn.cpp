// Author: NICOLA MARITAN

#include "pawn.h"
#include "board.h"

/*
    Costruttore della classe pawn. Essa semplicemente richiama il
    costruttore della base class piece.
*/
//pawn::pawn(const position& _pos, int _player, board* _running_board) : piece(_pos, _player, _running_board)
pawn::pawn(const position& _pos, int _player) : piece(_pos, _player)
{
    // Alla fine ho trovato un modo migliore :) ^ chiamata al base constructor
    /*
        C++ non permette di inizializzare var membro ereditate nel
        member initializer list di un construttore. Il valore di una
        var membro può essere inizializzata solo in una lista appartenente
        alla stesso classe della var.
    */
    /*pos = _pos;
    player = _player;
    */
}

void pawn::move(const position& to)
{
    
}

bool pawn::can_move_to(const position& pos)
{
    
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
        //possible_positions.push_back(pos + (sign * position(2, 0)));
    }
    /*possible_positions.push_back(pos + (sign * position(1, 0)));    // avanza di una casa in verticale
    possible_positions.push_back(pos + (sign * position(1, 1)));    // avanza di una casa in verticale e orizzontale
    possible_positions.push_back(pos + (sign * position(1, -1)));   
*/
    position p3;
    position p1(1, 2);
    position p2(2, 3);
    p3 = p1 + p2;
    std::cout << p1;

    return possible_positions;
}

