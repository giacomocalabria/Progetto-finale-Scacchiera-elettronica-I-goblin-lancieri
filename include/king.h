#ifndef KING_H
#define KING_H

#include "piece.h"

class king : public piece
{
    public:
        king(const position& _pos, int _player) : piece(_pos, _player){}
};

#endif