//Author: GIACOMO CALABRIA

#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include <iostream>

#include "player.h"

/*
    ---------------------------------------------------------------------------
    Classe derivata da player per il giocatore umano
    
    La classe human_player è la classe che implementa l'interfaccia con un 
    giocatore umano; tale classe riceve dall' utente i comandi e la classe pensa
    poi ad interfacciarsi con la board per eseguire la mossa data dai comandi.

    Per interfacciarsi con la board la classe ha bisogno di un riferimento ad 
    essa. Come per qualsiasi giocatore il giocatore umano ha un identificativo
    del giocatore player_id, necessario per garantire che il giocatore opera
    esclusivamente sui propri pezzi.
    ---------------------------------------------------------------------------
*/

class human_player : public player{
    public:
        human_player(board* _b, player_id _id)
            :player(_b, _id) {} //Chiamata al costruttore di player
        
        void turn() override;
    
    private:
        bool move() override;  
};

#endif // HUMAN_PLAYER_H