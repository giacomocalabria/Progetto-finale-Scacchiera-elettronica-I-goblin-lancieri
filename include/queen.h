#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class queen : public piece
{
    public:
        queen(const position& _pos, int _player) : piece(_pos, _player){}
};

#endif