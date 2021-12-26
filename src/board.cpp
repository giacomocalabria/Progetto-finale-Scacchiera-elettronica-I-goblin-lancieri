#include "board.h"

#include <vector>

using namespace std;


board::board()
{
    std::cout << "Board Initialization.\n";
    //init_game();
    //std::cout << "Game initialized.\n";
    to_empty();
    std::cout << "Emptied.\n";
    init_player_pieces();
    std::cout << "Board initializated.\n";
}

void board::move_piece(const position& from, const position& to)
{
    if (board_matrix[from.row][from.col] == nullptr)   // non c'è una pedina nella casella from
    {
        return; // da def, forse eccezione o altro
    }

    piece* p = board_matrix[from.row][from.col];
    if (p->can_move_to(to, board_matrix))
    {

        // MOMENTANEO WORK IN PROGRESS
        // aggiornare posizione in p
        p->set_position(to);
        board_matrix[to.row][to.col] = p;
        board_matrix[from.row][from.col] = nullptr;
        //p->move(position(to));
    }
    else
    {
        cout << "Mossa non valida. Da " << from << " a " << to << endl;
    }
    
}

void board::to_empty()
{
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            board_matrix[i][j] = nullptr;
        }
    }
}

void board::init_player_pieces()
{
    /*
        Inizializzza i pezzi dei giocatori, che sono:
            - 8 pawn ciascuno
            - 2 rook ciascuno
            - 2 bishop ciascuno
            - 2 pawn ciascuno
            - 1 king e 1 queen ciascuno
    */


    // ----------- Inserimento pawns ----------- 

    const int PAWN_ROW_PLAYER_2{1};  // Seconda riga dall'alto
    const int PAWN_ROW_PLAYER_1{6};   // Penultima riga dal basso

    for (int i = 0; i < PAWN_NUMBER; i++)
    {
        player_pawns[PLAYER_1].push_back(pawn(position(PAWN_ROW_PLAYER_1, i), PLAYER_1));
        player_pawns[PLAYER_2].push_back(pawn(position(PAWN_ROW_PLAYER_2, i), PLAYER_2));
        
    }
    for (int i = 0; i < PAWN_NUMBER; i++)
    {
        board_matrix[PAWN_ROW_PLAYER_2][i] = &player_pawns[PLAYER_2][i];
        board_matrix[PAWN_ROW_PLAYER_1][i] = &player_pawns[PLAYER_1][i];
    }


    // ----------- Inserimento knights ----------- 

    player_knights[PLAYER_1].push_back(knight(position(7, 1), PLAYER_1));
    player_knights[PLAYER_2].push_back(knight(position(0, 1), PLAYER_2));
    player_knights[PLAYER_1].push_back(knight(position(7, 6), PLAYER_1));
    player_knights[PLAYER_2].push_back(knight(position(0, 6), PLAYER_2));
    
    board_matrix[7][1] = &player_knights[PLAYER_1][0];
    board_matrix[0][1] = &player_knights[PLAYER_2][0];
    board_matrix[7][6] = &player_knights[PLAYER_1][1];
    board_matrix[0][6] = &player_knights[PLAYER_2][1]; 

    // ----------- Inserimento bishop ----------- 

    player_bishops[PLAYER_1].push_back(bishop(position(7, 2), PLAYER_1));
    player_bishops[PLAYER_2].push_back(bishop(position(0, 2), PLAYER_2));
    player_bishops[PLAYER_1].push_back(bishop(position(7, 5), PLAYER_1));
    player_bishops[PLAYER_2].push_back(bishop(position(0, 5), PLAYER_2));
    
    board_matrix[7][2] = &player_bishops[PLAYER_1][0];
    board_matrix[0][2] = &player_bishops[PLAYER_2][0];
    board_matrix[7][5] = &player_bishops[PLAYER_1][1];
    board_matrix[0][5] = &player_bishops[PLAYER_2][1];

    // ----------- Inserimento rook ----------- 

    player_rooks[PLAYER_1].push_back(rook(position(7, 0), PLAYER_1));
    player_rooks[PLAYER_2].push_back(rook(position(0, 0), PLAYER_2));
    player_rooks[PLAYER_1].push_back(rook(position(7, 7), PLAYER_1));
    player_rooks[PLAYER_2].push_back(rook(position(0, 7), PLAYER_2));
    
    board_matrix[7][0] = &player_rooks[PLAYER_1][0];
    board_matrix[0][0] = &player_rooks[PLAYER_2][0];
    board_matrix[7][7] = &player_rooks[PLAYER_1][1];
    board_matrix[0][7] = &player_rooks[PLAYER_2][1];

    // ----------- Inserimento queen -----------

    player_queen[PLAYER_1].push_back(queen(position(0, 3), PLAYER_1));
    player_queen[PLAYER_2].push_back(queen(position(7, 3), PLAYER_2));

    board_matrix[7][3] = &player_queen[PLAYER_1][0];
    board_matrix[0][3] = &player_queen[PLAYER_2][0];

    // ----------- Inserimento king -----------

    player_king[PLAYER_1].push_back(king(position(0, 4), PLAYER_1));
    player_king[PLAYER_2].push_back(king(position(7, 4), PLAYER_2));

    board_matrix[7][4] = &player_king[PLAYER_1][0];
    board_matrix[0][4] = &player_king[PLAYER_2][0];

    // work in progress, mancano ovviamnete gli altri pezzi
    /*
    const int NOT_PAWN_ROW_PLAYER_2{0};
    const int NOT_PAWN_ROW_PLAYER_1{7};
    player_pieces[PLAYER_1].push_back(rook(position(NOT_PAWN_ROW_PLAYER_1, 0), PLAYER_1));*/
    
}

void board::print_board()
{
   for (int i = 0; i < board_size; i++)
   {
       std::cout << board_size - i << " ";

       for (int j = 0; j < board_size; j++)
       {
           piece* p = board_matrix[i][j];
           if (p == nullptr)
           {
               std::cout << "/";
           }
           else
           {
               std::cout << p->symbol();
               //std::cout << "*";
           }
           
       }
       std::cout << std::endl;
   }
   std::cout << "  ABCDEFGH\n";

}