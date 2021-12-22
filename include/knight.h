// Author: GIACOMO CALABRIA

/*  ----------------------------------------------------
    Classe del knight/cavallo.
    ----------------------------------------------------
*/

#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class knight : public piece{
    public:
        //pawn(const position& _pos, int _player, board* _running_board);
        knight(const position& _pos, int _player);
        void move(const position& to) override;
        bool can_move_to(const position& dest, piece* const mat[][8]) override;
        inline char symbol() override;

    private:
        std::vector<position> get_possible_positions() override;    
};

#endif //KNIGHT_h