// Author: NICOLA MARITAN

#include "pawn.h"
#include "board.h"

/*
    Costruttore della classe pawn. Essa semplicemente richiama il
    costruttore della base class piece.
*/
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

char pawn::symbol()
{
    if (player == board::PLAYER_1)    // Player 1
        return 'p';
    return 'P'; // Player 2
}

std::vector<position> pawn::get_possible_positions()
{

}

