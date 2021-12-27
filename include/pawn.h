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
        bool can_move_to(const position& dest, const std::vector<piece*>& board_pieces) override;
        bool can_eat(const position& dest, const std::vector<piece*>& board_pieces) override;
        inline char symbol() override;
        std::vector<position> get_possible_positions() override;

    private:
        bool is_init_pos {true};
        
};

#endif