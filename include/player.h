#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "piece.h"
#include "player_id.h"

/*
    -------------------------------------------------------------------
    La classe player è una virtuale pura. Le sue
    classe derivate hanno il compito di interfacciarsi
    con la board operando su di essa. Le due funzioni membro
    principali sono:
    
    turn: da inizio all'intero turno del giocatore, dunque all'interno
    di essa viene chiamata la funzione move più volte finché essa non
    gestisce un caso valido.

    move: gestisce la mossa di un pezzo. Chiama sulla board move_piece,
    che appunto muove concretamente i pezzi. E' il punto di contatto
    fra board e player.
    -------------------------------------------------------------------
*/

class player{

    public:
        player(board* _b, player_id _id) : b{_b}, id{_id}{};
        player_id get_player_number(){return id;}
        virtual void turn() = 0;

    protected:
        board* b;
        player_id id;
        virtual bool move() = 0;
};

#endif // PLAYER_H