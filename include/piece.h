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
        piece(const position& _pos, player_id _player) : player{_player}
        {
            if (!is_valid_position_8(_pos)) throw bad_position_8();
            pos = _pos;
        };

        virtual bool can_move_to(const position& dest, const std::vector<piece*>& board_pieces) = 0;
        virtual bool can_capture(const position& dest, const std::vector<piece*>& board_pieces) = 0;
        virtual bool get_can_be_passed() = 0;
        virtual char symbol() = 0;
        virtual std::vector<position> get_possible_positions() = 0;

        // Setters e getters
        position get_position(){return pos;}
        void set_position(position new_pos){pos = new_pos;}
        player_id get_player(){return player;}
        bool get_init_pos(){return is_init_pos;}
        void set_init_pos_to_false(){is_init_pos = false;}
        
    protected:
        // variabili di esemplare
        player_id player; 
        position pos;
        bool is_init_pos {true};
        
};

/*
    Funzioni che prendono come parametro un puntatore
    ad un pezzo e restituiscono true se e solo se
    sono un'istanza di quel particolare pezzo.
    Molto più elegante di un upcast, sfrutta la
    funzione membro virtuale pura symbol di ciascun
    pezzo per dedurne univocamente la natura.
*/
bool is_pawn(piece* p);
bool is_king(piece* p);
bool is_queen(piece* p);
bool is_rook(piece* p);
bool is_knight(piece* p);
bool is_bishop(piece* p);

#endif // PIECE_H