// Author: GIACOMO CALABRIA

/*  ----------------------------------------------------
    Classe derivata da piece del knight/cavallo.
    ----------------------------------------------------
*/

#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class knight : public piece{
    public:
        knight(const position& _pos, int _player) : piece(_pos, _player){}
        bool can_move_to(const position& dest, const std::vector<piece*>& board_pieces) override;
        bool can_eat(const position& dest, const std::vector<piece*>& board_pieces) override;
        inline char symbol() override;
        std::vector<position> get_possible_positions() override;    
};

#endif //KNIGHT_H