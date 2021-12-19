#ifndef PIECE_H
#define PIECE_H
#include "position.h"
#include <vector>

//classe virtuale pura

class piece
{   
public:
    virtual void move(const Position& dest) = 0; //funzione virtuale pura
    virtual std::vector<Position> av_dest() = 0; //destinazioni disponibili
protected:
    bool color; //bianco -> true ; nero -> false
    Position pos; //posizione attuale del pezzo
};

#endif