// Author: NICOLA MARITAN

#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include <chrono>
#include <ctime>
#include <random>

#include "player.h"


/*
    ----------------------------------------------------
    La classe computer_player si interfaccia con la board
    in modo tale da operare su di essa in modo casuale.
    ----------------------------------------------------
*/

class computer_player : public player
{
    public:
        computer_player(board* _b, player_id _id) : player(_b, id), generator(std::chrono::system_clock::now().time_since_epoch().count() * 5 * id){};
        void turn() override;
    protected:
        bool move() override;
        
        /*
            std::default_random_engine generator;
            E' necessario che il generatore sia un membro della classe, dal momento che
            il seed deve essere impostato alla creazione della classe: se così non fosse
            allora sarebbe creato ad ogni chiamata funzione move, cosa che potrebbe rendere
            i fenomeni aleatori poco imprevedibili.
        */
        std::default_random_engine generator;
};



#endif // COMPUTER_PLAYER_H