#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class bishop : public piece
{
    public:
        bishop(const position& _pos, int _player) : piece(_pos, _player){}
};

#endif