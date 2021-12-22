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
        void move(const position& to) override;
        bool can_move_to(const position& dest, piece* const mat[][8]) override;
        inline char symbol() override;

    private:
        std::vector<position> get_possible_positions() override;

    private:
        bool is_init_pos {true};
        
};

#endif