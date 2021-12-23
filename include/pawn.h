// Author: NICOLA MARITAN

/*  ----------------------------------------------------
    Classe del pawn/pedone.
    ----------------------------------------------------
*/

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class pawn : public piece
{
    public:
        //pawn(const position& _pos, int _player, board* _running_board);
        pawn(const position& _pos, int _player);
        bool can_move_to(const position& dest, piece* const mat[][max_position]) override;
        inline char symbol() override;

    private:
        std::vector<position> get_possible_positions() override;

    private:
        bool is_init_pos {true};
        
};

#endif