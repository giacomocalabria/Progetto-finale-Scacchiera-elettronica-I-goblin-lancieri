// Author: NICOLA MARITAN

#ifndef BOARD_H
#define BOARD_H

#include <fstream>
#include <iostream>
#include <vector>
//#include <stdlib.h> 

#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

class board
{
    public:
        board();
        void to_empty();    // rende la board priva di pezzi
        bool move_piece(const position& from, const position& to);
        void init_game();
        void init_board();

    
    public:
        void print_board();
        void file_print_board(std::ofstream& _out_file);
        piece* get_board_piece(position pos){return board_matrix[make_index_8(pos)];}
        void set_board_piece(position pos, piece* p){board_matrix[make_index_8(pos)] = p;}
        std::vector<position> get_player_pieces_positions(player_id player);
        
        static const int board_size {8};
        static const int PLAYER_1{0}; //fare un enum?
        static const int PLAYER_2{1};

        //void check_king_movement();
        bool is_check(player_id player_number);
        bool is_checkmate(player_id player_number);

        bool is_draw();
        
        
        //bool is_checkmate2(int player_number);

        bool is_castling(const position& from, const position& to);
        bool can_en_passant(const position& passing, const position& to_pass);
        //bool can_en_passant(piece* pce, piece* pce_to_pass);
    
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
    /*
        Variabili membro private
    */
    private:
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
    
    /*
        Funzioni membro privato.
    */   
    private:   
        void init_player_pieces();
        bool promote(const position& pos);

    private:
        int count_draw = 0;         //tiene conto del numero di mosse fatte da tutti e 2 i giocatori
        int no_pwn_no_eat = 0;      //tiene conto del numero di mosse senza mangiate e senza movimenti di pawn

    public:
        int get_count_draw() {return count_draw;}
        int get_no_pwn_no_eat() {return no_pwn_no_eat;}

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
};

#endif // BOARD_H