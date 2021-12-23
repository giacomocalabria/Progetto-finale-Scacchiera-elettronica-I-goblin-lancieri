//Autore: EDDIE CARRARO

#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class bishop : public piece
{   
    public:
        bishop(const position& _pos, int _player) : piece(_pos, _player){}
        void move(const position& to) override;
        bool can_move_to(const position& dest, piece* const mat[][8]) override;
        inline char symbol() override;// -  -  -  - > giocatore 1 o 2
    private:
        std::vector<position> get_possible_positions() override;
};

#endif