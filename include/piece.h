// Author: NICOLA MARITAN

/* ----------------------------------------------------
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
        piece(const position& _pos, int _player) : pos{_pos}, player{_player}{};
        virtual void move(const position& to) = 0;
        virtual bool can_move_to(const position& pos) = 0;
        virtual char symbol() = 0;

        // spunti
        void eat(const piece& other);
        position get_position(){return pos;}
        

    protected:
        // funzioni membro protette
        virtual std::vector<position> get_possible_positions() = 0;

        // come vengono chiamate nn ricordo
        int player; // 1 o 2 - tipo di dato da definire
        position pos;
};

#endif