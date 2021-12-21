// Author: NICOLA MARITAN

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "piece.h"
#include "pawn.h"
/*#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"*/

class board
{
    public:
        board();
        void to_empty();
        void move_piece(const position& from, const position& to);
        void print_board();
        // --
        piece* get_board_piece(position pos){return board_matrix[pos.row][pos.col];}
        void set_board_piece(position pos, piece* p){board_matrix[pos.row][pos.col] = p;}
        
        static const int board_size {8};
        static const int PLAYER_1{0};
        static const int PLAYER_2{1};

    
    private:
        /*
            Costanti relative al numero di pezzi di ogni giocatore.
        */
        const int PAWN_NUMBER{8};
        const int ROOK_NUMBER{2};
        const int BISHOP_NUMBER{2};
        const int KING_NUMBER{1};
        const int QUEEN_NUMBER{1};

    /*
        Variabili membro private
    */
    private:
        piece* board_matrix[board_size][board_size];
        
        /* 
            Array di dimensione 2, contenenti i vector dei pezzi dei giocatori 1 e 2.
            In questo modo per accedere ai pezzi del giocatore 2 basta
            la notazione player_pieces[1].
        */
        //std::vector<piece*> player_pieces[2];

        std::vector<pawn> player_pawns[2];
        /*std::vector<rook> player_rooks[2];
        std::vector<bishop> player_bishops[2];
        */

    /*
        Funzioni membro privato.
    */   
    private:   
        void init_player_pieces();
};

#endif