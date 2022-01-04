// Author: NICOLA MARITAN

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <fstream>
#include <vector>
#include "pawn.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"

class board
{
    public:
        board();
        void to_empty();    // rende la board priva di pezzi
        bool move_piece(const position& from, const position& to);
        //bool move_piece_2(const position& from, const position& to);
        void init_game();
        void init_board();


    
    public:
        void print_board();
        void file_print_board(std::ofstream& _out_file);
        //std::ostream& operator<<(std::ostream& os);
        //std::ifstream& operator<<(std::ostream& os);
        // --
        piece* get_board_piece(position pos){return board_matrix[make_index_8(pos)];}
        void set_board_piece(position pos, piece* p){board_matrix[make_index_8(pos)] = p;}
        std::vector<position> get_player_pieces_positions(int player);
        
        static const int board_size {8};
        static const int PLAYER_1{0}; //fare un enum?
        static const int PLAYER_2{1};

        //void check_king_movement();
        bool is_check(int player_number);
        bool is_checkmate(int player_number);
        bool is_checkmate2(int player_number);

    
    private:
        /*
            Costanti relative al numero di pezzi di ogni giocatore.
        */
        /*const int PAWN_NUMBER{8}; //fare un enum?
        const int ROOK_NUMBER{2};
        const int BISHOP_NUMBER{2};
        const int KING_NUMBER{1};
        const int QUEEN_NUMBER{1};
        const int KNIGHT_NUMBER{2};*/
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
        // piece* board_matrix[board_size][board_size];
        std::vector<piece*> board_matrix;
        
        /* 
            Array di dimensione 2, contenenti i vector dei pezzi dei giocatori 1 e 2.
            In questo modo per accedere ai pezzi del giocatore 2 basta
            la notazione player_pieces[1].
        */

        std::vector<pawn> player_pawns[2];
        std::vector<knight> player_knights[2];
        std::vector<rook> player_rooks[2];
        std::vector<bishop> player_bishops[2];
        std::vector<king> player_king[2];
        std::vector<queen> player_queen[2];
    /*
        Funzioni membro privato.
    */   
    private:   
        void init_player_pieces();
        bool promote(const position& pos);

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

#endif