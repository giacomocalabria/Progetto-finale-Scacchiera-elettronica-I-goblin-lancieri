//Author: NICOLA MARITAN

/*  ----------------------------------------------------
    Classe derivata da piece del king/re.
    Chiaramente il re assume una importanza a se' per il
    flusso del gioco degli scacchi. Oltre alle funzioni
    membro virtuali della classe piece tale classe e'
    dotata della funz. membro is_check, la quale controlla
    se il re si trova nella posizione di scacco, cioe'
    se esso puo' essere "mangiato" da un pezzo avversario.
    Tale funzione membro e' richiamata dalla board
    a seconda dell'id del pezzo (vedasi is_check nella classe
    board).
    ----------------------------------------------------
*/

#ifndef KING_H
#define KING_H

#include "piece.h"

class king : public piece
{
    public:
        king(const position& _pos, player_id _player) : piece(_pos, _player){}

        // Return r/R (re)
        inline char symbol() override;

        // Puo' muoversi verso tale destinazione?
        bool can_move_to(const position& dest, const std::vector<piece*>& board_pieces) override;

        // Puo' catturare il pezzo (ammesso esista) in tale destinazione?
        bool can_capture(const position& dest, const std::vector<piece*>& board_pieces) override;

        // Il re non puo' subire l'en passant
        bool get_can_be_passed() override {return false;}
        
        // Quali sono le possibili posizioni di questo pezzo?
        std::vector<position> get_possible_positions() override;
         
    public:
        // Funzione membro che controlla se il re e' sotto scacco
        bool is_check(const std::vector<piece*>& board_pieces);
};

#endif //KING_H