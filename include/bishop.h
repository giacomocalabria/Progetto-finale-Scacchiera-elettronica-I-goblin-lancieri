//Autore: EDDIE CARRARO

#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class bishop : public piece
{
    public:
        bishop(const position& _pos, int _player) : piece(_pos, _player){}

        void move(const position& to);
        bool can_move_to(const position& dest, piece* const mat[][8]);

       // bool can_eat(); //NON SERVE

        char symbol(); // -  -  -  - > giocatore 1 o 2



    protected:
        std::vector<position> get_possible_positions();

};

#endif