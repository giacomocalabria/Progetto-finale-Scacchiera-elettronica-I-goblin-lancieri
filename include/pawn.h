// Author: NICOLA MARITAN

/* ----------------------------------------------------
    Classe del pawn/pedone.
    ----------------------------------------------------
*/

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class pawn : public piece
{
    public:


    protected:
        std::vector<position> get_possible_positions() override;
        
};

#endif