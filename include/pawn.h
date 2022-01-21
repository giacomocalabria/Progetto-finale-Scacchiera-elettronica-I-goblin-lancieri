// Author: NICOLA MARITAN

/*  
    ----------------------------------------------------
    Classe derivata da piece del pawn/pedone.
    ----------------------------------------------------
*/

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class pawn : public piece
{
    public:
        pawn(const position& _pos, player_id _player);
        // Puo' muoversi verso tale destinazione?
        bool can_move_to(const position& dest, const std::vector<piece*>& board_pieces) override;
        // Puo' catturare il pezzo (ammesso esista) in tale destinazione?
        bool can_capture(const position& dest, const std::vector<piece*>& board_pieces) override;
        // Return p/P
        inline char symbol() override;
        // Quali sono le possibili posizioni di questo pezzo?
        std::vector<position> get_possible_positions() override;

    private:
        /* 
            Can_be_passed e' una variabile booleana che ci dice se un pedone puo' essere
            catturato mediante en passant (in quel caso, can_be_passed = true).
        */
        bool can_be_passed {false};

    public:
        /*
            La funzione virtuale pura assume un comportamento particolare nel caso
            del pedone, in quanto e' l'unico pezzo che puo' essere catturato per
            en passant. Dunque il suo comportamento e' personalizzato per il pedone.
            Gli altri pezzi restituiscono false. Il pedone restituisce il valore di
            can_be_passed.
        */
        bool get_can_be_passed() override {return can_be_passed;}
        void set_can_be_passed(bool bl) {can_be_passed = bl;}
        
};

#endif // PAWN_H