// Author: NICOLA MARITAN

/*  ----------------------------------------------------
    Classe virtuale pura. Classe da cui discendono le
    classi dei vari pezzi. Contiene funzioni membro di
    utilità generale per una generica classe di tipo
    pezzo.
    ----------------------------------------------------
*/

#ifndef PIECE_H
#define PIECE_H

//classe virtuale pura
#include "position.h"
#include <vector>

class piece
{
    public:
        static constexpr int max_position {8};
        static constexpr int min_position {0};

    public:
        piece(const position& _pos, int _player) : pos{_pos}, player{_player}{};
        virtual bool can_move_to(const position& dest, const std::vector<piece*>& board_pieces) = 0;
        virtual char symbol() = 0;

        // spunti
        //void eat(const piece& other);

        position get_position(){return pos;}
        void set_position(position new_pos){pos = new_pos;}
        int get_player(){return player;}
        virtual std::vector<position> get_possible_positions() = 0;
        
    protected:
        // variabili di esemplare
        int player; // 1 o 2 - tipo di dato da definire
        position pos;
        
};

#endif