// Author: NICOLA MARITAN

#ifndef BOARD_H
#define BOARD_H

#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

/*  
    ----------------------------------------------------
    La classe board contiene concretamente i pezzi e
    interfaccia i player con essi. Fornisce controlli
    sul flusso della partita, la sua visualizzazione,
    sullo scacco (attraverso i king) e sullo scacco
    matto.
    ----------------------------------------------------
*/

class board
{
    public:
        // ------------------ Costruttore e inizializzatori ------------------
        board();
        void to_empty();    // rende la board priva di pezzi
        bool move_piece(const position& from, const position& to);
        void init_game();
        void init_board();

        // ------------------ Funzioni membro pubbliche ------------------
        inline std::vector<std::string> get_log() { return log; }
        std::string row_symbols(int i);
        std::string all_board_symbols();
        void print_board();
        void file_print_board(std::ofstream& _out_file);
        piece* get_board_piece(const position& pos){return board_matrix.at(make_index_8(pos));}
        std::vector<position> get_player_pieces_positions(player_id player);
        std::vector<position> get_player_in_board_pieces_positions(player_id player);

        // Lato della board        
        static const int board_size {8};

        // ------------------ Funzioni membro di stato ------------------
        bool is_check(player_id player_number);
        bool is_checkmate(player_id player_number);
        bool is_draw(player_id pl);
        bool has_king_been_captured(player_id id);
        bool is_castling(const position& from, const position& to);
        bool can_en_passant(const position& passing, const position& to_pass);
        int get_count_draw() {return count_draw;}
        int get_no_pwn_no_eat() {return no_pwn_no_eat;}

        // ------------------ Funzioni membro di inserimento ------------------
    private:
        void insert_pawn(const position& pos, player_id id);
        void insert_king(const position& pos, player_id id);
        void insert_queen(const position& pos, player_id id);
        void insert_rook(const position& pos, player_id id);
        void insert_bishop(const position& pos, player_id id);
        void insert_knight(const position& pos, player_id id);

        class too_many_pieces{};
    
    // Costanti relative al numero di pezzi di ogni giocatore.
    private:
        enum piece_numbers
        {
            king_number = 1,
            queen_number = 1,
            knight_number = 2,
            bishop_number = 2,
            rook_number = 2,
            pawn_number = 8
        };

        // ------------------ Variabili membro private ------------------

        /*
            Board concreata di puntatori a piece. L'accesso alla cella di
            di riga i e colonna j avviene tramite la formula 8*i + j.
            A tal proposito vi e' l'uso massiccio della funzione make_index_8
            definita in position.h che si occupa di questo calcolo.
        */
        std::vector<piece*> board_matrix;
        
        /* 
            Array di dimensione 2, contenenti i vector dei pezzi dei giocatori 1 e 2.
            In questo modo per accedere ai pezzi del giocatore X basta
            la notazione player_piece[PLAYER_X].
            
            Essi sono di fatto dei contenitore statici dei pezzi della board:
            la loro capacità non cambia durante l'esecuzione del programma,
            poiché in init_board per ognuno di questi vector vi è un reserve
            della memoria necessaria. La staticità dei vector è indispensabile
            in quanto una riallocazione della memoria nel freestore di un vector
            rende in generale invalidi i riferimenti nella board. In questo modo
            si evita ogni tipo di memory leak in quanto l'allocazione dinamica
            della memoria è gestita dai vector stessi della STL, e si dispone
            di un modo molto comodo per avere a disposizione i vari pezzi.  
            In questo modo per accedere ai pezzi del giocatore 2 basta la notazione player_pieces[1].
        */
        std::vector<pawn> player_pawns[player_id::player_count];
        std::vector<knight> player_knights[player_id::player_count];
        std::vector<rook> player_rooks[player_id::player_count];
        std::vector<bishop> player_bishops[player_id::player_count];
        std::vector<king> player_king[player_id::player_count];
        std::vector<queen> player_queen[player_id::player_count];
    
        // ------------------ Funzioni membro private ------------------
    private:   
        void init_player_pieces();
        bool promote(const position& pos);
        bool can_do_legal_move(player_id pl);

    private:
        int count_draw = 0;         // tiene conto del numero di mosse fatte da tutti e 2 i giocatori
        int no_pwn_no_eat = 0;      // tiene conto del numero di mosse senza mangiate e senza movimenti di pawn
        std::map<std::string, int> states;    // mappa che contiene le varie "posizioni" della scacchiera e il numero di volte che si sono presentate durante una partita
        std::vector<std::string> log; // Vector per memorizzare tutte le mosse effettuate dai giocatori


    // -------------- setup di debug --------------
    private:
        // Cheat della board, setup pre impostati
        void setup_1();
        void setup_2();
        void setup_3();
        void setup_4();
        void setup_5();
        void setup_6();
        void setup_7();
        void setup_8();
        void setup_9();
};

#endif // BOARD_H