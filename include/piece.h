// Author: EDDIE CARRARO

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


        /*  -----------------------------------------------------------------
            Funzione che dice se il pezzo puo' spostarsi nella posizione dest
            -----------------------------------------------------------------
        */
        virtual bool can_move_to(const position& dest, const std::vector<piece*>& board_pieces) = 0;


        /*  -----------------------------------------------------------------------------------
            Mi dice se il pezzo in questione puo' catturare il pezzo avente come posizione dest
            (richiama can_move_to per tutti i tipi di pedine, eccetto che per pawn (il quale ha
            direzioni differenti in base a quel che vuole fare: catturare o muoversi. In
            effetti tutte le pedine, eccetto i pedoni, in una certa direzione possono sia
            muoversi che catturare)).
            -----------------------------------------------------------------------------------
        */
        virtual bool can_capture(const position& dest, const std::vector<piece*>& board_pieces) = 0;


        /*  ---------------------------------------------------------------------------------
            Restituisce la variabile can_be_passed, la quale mi dice se una certa pedina puo'
            subire l'en passant (ovviamente, per definizione, can_be_passed puo' essere true
            solo nei pedoni)
            ---------------------------------------------------------------------------------
        */
        virtual bool get_can_be_passed() = 0;


        /*  -------------------------------------------------------------------
            Restituisce il simbolo (da inserire in una scacchiera) della pedina
            -------------------------------------------------------------------
        */
        virtual char symbol() = 0;


        /*  -----------------------------------------------------------------------------------
            Restituisce un vector contenente tutte le posizioni in cui una pedina puo' muoversi
            (senza contare le interazioni con le altre, alle quali ci pensa can_move_to)
            -----------------------------------------------------------------------------------
        */
        virtual std::vector<position> get_possible_positions() = 0;

        // Setters e getters
        position get_position(){return pos;}
        void set_position(position new_pos){pos = new_pos;}
        player_id get_player(){return player;}
        bool get_init_pos(){return is_init_pos;}
        void set_init_pos_to_false(){is_init_pos = false;}
        
    protected:
        // variabili di esemplare

        /*  ----------------------------------------------------
            Ci suggerisce a quale giocatore appartiene la pedina
            ----------------------------------------------------
        */
        player_id player; 


        /*  -----------------------------------------------------------------------------------
            Posizione della pedina nella scacchiera
            -----------------------------------------------------------------------------------
        */
        position pos;


        /*  --------------------------------------------------------------------------------
            Ci dice se la pedina deve ancora muoversi o meno (serve soprattutto ai pedoni, i
            quali possono fare il doppio passo solo se non hanno ancora fatto alcuna mossa e
            al re per poter fare l'arrocco)
            --------------------------------------------------------------------------------
        */
        bool is_init_pos {true};    //
};

/*  -------------------------------------------------
    Funzioni che prendono come parametro un puntatore
    ad un pezzo e restituiscono true se e solo se
    sono un'istanza di quel particolare pezzo.
    Molto più elegante di un upcast, sfrutta la
    funzione membro virtuale pura symbol di ciascun
    pezzo per dedurne univocamente la natura.
    -------------------------------------------------
*/
bool is_pawn(piece* p);
bool is_king(piece* p);
bool is_queen(piece* p);
bool is_rook(piece* p);
bool is_knight(piece* p);
bool is_bishop(piece* p);

#endif // PIECE_H