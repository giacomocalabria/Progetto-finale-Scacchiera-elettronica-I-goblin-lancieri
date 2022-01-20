// Author: NICOLA MARITAN

/*  
    ----------------------------------------------------
    Classe derivata da piece del pawn/pedone.
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
        /* 
            Can_be_passed e' una variabile booleana che ci dice se un pedone puo' essere
            catturato mediante en passant (in quel caso, can_be_passed = true).
        */
        bool can_be_passed {false};

    public:
        bool get_can_be_passed() override {return can_be_passed;}
        void set_can_be_passed(bool bl) {can_be_passed = bl;}
        
};

#endif // PAWN_H