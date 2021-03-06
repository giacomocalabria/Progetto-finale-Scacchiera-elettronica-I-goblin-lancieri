//Autore: EDDIE CARRARO

/*  
    ----------------------------------------------------
    Classe derivata da piece del bishop/alfiere.
    ----------------------------------------------------
*/

#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class bishop : public piece
{   
    public:
        bishop(const position& _pos, player_id _player) : piece(_pos, _player){}
        bool can_move_to(const position& dest, const std::vector<piece*>& board_pieces) override;
        bool can_capture(const position& dest, const std::vector<piece*>& board_pieces) override;
        bool get_can_be_passed() override {return false;}
        inline char symbol() override;
        std::vector<position> get_possible_positions() override;
};

#endif // BISHOP_H