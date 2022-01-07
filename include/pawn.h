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
        pawn(const position& _pos, player_id _player);
        bool can_move_to(const position& dest, const std::vector<piece*>& board_pieces) override;
        bool can_capture(const position& dest, const std::vector<piece*>& board_pieces) override;
        bool can_promote() override;
        inline char symbol() override;
        std::vector<position> get_possible_positions() override;

    /*private:
        bool is_init_pos {true};*/
    private:
        bool is_init_pos {true};
        bool can_be_passed {false};

    public:
        bool get_can_be_passed() override {return can_be_passed;}
        
};

#endif // PAWN_H