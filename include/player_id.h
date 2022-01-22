// Author: NICOLA MARITAN

/*
    Semplice plain enumration contenente info su
    numeri chiave dei giocatori, il loro id
    e il loro conteggio.
*/

#ifndef PLAYER_ID_H
#define PLAYER_ID_H

enum player_id
{
    // Conteggio del numero di giocatori
    player_count = 2,

    // Nessun player e' un caso contemplato
    no_player = -1,

    // I due giocatori
    player_1 = 0,
    player_2 = 1, 
};

#endif // PLAYER_ID_H