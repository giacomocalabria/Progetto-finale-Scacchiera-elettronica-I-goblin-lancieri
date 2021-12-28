// Author: NICOLA MARITAN

/*
*/

#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "player.h"
#include <random>
#include <ctime>
#include <chrono>

class computer_player : public player
{
    public:
        computer_player(board* _b, int _player_number) : player(_b, _player_number), generator(std::chrono::system_clock::now().time_since_epoch().count() * 5 * player_number){};
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



#endif