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

#include <vector>

#include "player_id.h"
#include "position.h"

class piece
{
    public:
        static constexpr int max_position {8};
        static constexpr int min_position {0};

    public:
        piece(const position& _pos, player_id _player) : pos{_pos}, player{_player}{};

        virtual bool can_move_to(const position& dest, const std::vector<piece*>& board_pieces) = 0;
        virtual bool can_capture(const position& dest, const std::vector<piece*>& board_pieces) = 0;
        virtual bool can_promote() = 0;
        virtual char symbol() = 0;
        virtual std::vector<position> get_possible_positions() = 0;

        position get_position(){return pos;}
        void set_position(position new_pos){pos = new_pos;}
        
        player_id get_player(){return player;}

        bool get_init_pos(){return is_init_pos;}
        void set_init_pos(){is_init_pos = false;}
        
    protected:
        // variabili di esemplare
        player_id player; 
        position pos;
        bool is_init_pos {true};
        
};

#endif // PIECE_H