//author: GIACOMO CALABRIA

#ifndef REPLAY_PLAYER_H
#define REPLAY_PLAYER_H

#include <string>

#include "board.h"

/*  -----------------------------------------------------------------------------------
    Questo giocatore virtuale si occupa di gestire il replay del gioco. Viene costruito
    sulla board e opera attraverso il metodo turn, che a sua volta invocherà il metodo 
    move_piece della board.

    Il file di replay è stato costruito in modo tale che al suo interno vengano messe solo mosse valide/lecite. Per tanto non è nemmeno necessario creare due giocatori di 
    tipo replay in quanto basta un solo giocatore che esegue le mosse nell' ordine 
    indicato dal file di replay
    -----------------------------------------------------------------------------------
*/

class replay_player{
    public:
        replay_player(board* _b) : b{_b}{};
        void turn(std::string& mossa);
    
    private:
        board* b; //Riferimento alla board necessario per chiamare il metodo move_piece
};

#endif // REPLAY_PLAYER_H