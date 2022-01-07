// Author: NICOLA MARITAN

#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include <chrono>
#include <ctime>
#include <iostream>
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
        computer_player(board* _b, player_id _id) : player(_b, _id)
        {
            //std::cout << "computer_player_constructor; my id: " << id << std::endl;
        };
        void turn() override;
    protected:
        bool move() override;
};



#endif // COMPUTER_PLAYER_H