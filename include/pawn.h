// Author: EDDIE CARRARO

/*  
    ----------------------------------------------------
    Classe derivata del pawn/pedone.
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
        inline char symbol() override;
        std::vector<position> get_possible_positions() override;

    private:
        bool can_be_passed {false};

    public:
        bool get_can_be_passed() override {return can_be_passed;}
        void set_can_be_passed(bool bl) {can_be_passed = bl;}
        
};

#endif // PAWN_H