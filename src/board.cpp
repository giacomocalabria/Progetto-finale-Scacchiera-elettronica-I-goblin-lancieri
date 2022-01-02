#include "board.h"
#include <vector>

using namespace std;


board::board()
{
    std::cout << "Board Initialization.\n";
    //init_game();
    //std::cout << "Game initialized.\n";
    //to_empty();
    //std::cout << "Emptied.\n";
    
    init_board();

    #define SETUP 1
    #if SETUP
        setup_6();
    #else
        init_player_pieces();
    #endif
    std::cout << "Board initializated.\n";
}

/*
    Setup 1:
     01234567
    0/A//T///
    1//////A/
    2////r//T
    3////////
    4////////
    5////////
    6////////
    7////////

    Test: Verificare la condizione di scacco matto.
*/
void board::setup_1()
{
    player_bishops[PLAYER_2].push_back(bishop(position(0, 2), PLAYER_2));
    player_rooks[PLAYER_2].push_back(rook(position(0, 4), PLAYER_2));
    player_king[PLAYER_1].push_back(king(position(2, 4), PLAYER_1));
    player_bishops[PLAYER_2].push_back(bishop(position(0, 6), PLAYER_2));
    player_rooks[PLAYER_2].push_back(rook(position(2, 7), PLAYER_2));


    board_matrix[make_index_8(0, 2)] = &player_bishops[PLAYER_2][0];
    board_matrix[make_index_8(0, 4)] = &player_rooks[PLAYER_2][0];
    board_matrix[make_index_8(2, 4)] = &player_king[PLAYER_1][0];
    board_matrix[make_index_8(0, 6)] = &player_bishops[PLAYER_2][1];
    board_matrix[make_index_8(2, 7)] = &player_rooks[PLAYER_2][1];

}

/*
    Setup 2:
     01234567
    0/A//T///
    1//////A/
    2///Pr//T
    3////////
    4////////
    5////////
    6////////
    7////////

    Test: Verificare la condizione di scacco matto.
*/
void board::setup_2()
{
    player_bishops[PLAYER_2].push_back(bishop(position(0, 2), PLAYER_2));
    player_rooks[PLAYER_2].push_back(rook(position(0, 4), PLAYER_2));
    player_king[PLAYER_1].push_back(king(position(2, 4), PLAYER_1));
    player_bishops[PLAYER_2].push_back(bishop(position(0, 6), PLAYER_2));
    player_rooks[PLAYER_2].push_back(rook(position(2, 7), PLAYER_2));
    player_pawns[PLAYER_2].push_back(pawn(position(2, 3), PLAYER_2));


    board_matrix[make_index_8(0, 2)] = &player_bishops[PLAYER_2][0];
    board_matrix[make_index_8(0, 4)] = &player_rooks[PLAYER_2][0];
    board_matrix[make_index_8(2, 4)] = &player_king[PLAYER_1][0];
    board_matrix[make_index_8(0, 6)] = &player_bishops[PLAYER_2][1];
    board_matrix[make_index_8(2, 7)] = &player_rooks[PLAYER_2][1];
    board_matrix[make_index_8(2, 3)] = &player_pawns[PLAYER_2][0];
}

/*
    Setup 3:
     01234567
    0////////
    1/////P//
    2////r///
    3////////
    4////////
    5////////
    6////////
    7////////

    Test: Verificare la condizione di scacco matto.
*/
void board::setup_3()
{
    player_king[PLAYER_1].push_back(king(position(2, 4), PLAYER_1));
    player_pawns[PLAYER_2].push_back(pawn(position(1, 5), PLAYER_2));

    board_matrix[make_index_8(2, 4)] = &player_king[PLAYER_1][0];
    board_matrix[make_index_8(1, 5)] = &player_pawns[PLAYER_2][0];
}

/*
    Setup 4:
     01234567
    0////T///
    1////////
    2////r/a/
    3////////
    4////////
    5////////
    6////////
    7////////

    Test: Verificare la condizione di scacco matto.
*/
void board::setup_4()
{
    player_king[PLAYER_1].push_back(king(position(2, 4), PLAYER_1));
    player_rooks[PLAYER_2].push_back(rook(position(0, 4), PLAYER_2));
    player_bishops[PLAYER_1].push_back(bishop(position(2, 6), PLAYER_1));

    board_matrix[make_index_8(2, 4)] = &player_king[PLAYER_1][0];
    board_matrix[make_index_8(0, 4)] = &player_rooks[PLAYER_2][0];
    board_matrix[make_index_8(2, 6)] = & player_bishops[PLAYER_1][0];
}

/*
    Setup 5:
     01234567
    0///////A
    1T///////
    2////r///
    3T///////
    4///T/T//
    5////////
    6////////
    7////////

    Test: Verificare la condizione di scacco matto.
*/
void board::setup_5()
{
    player_king[PLAYER_1].push_back(king(position(2, 4), PLAYER_1));

    player_rooks[PLAYER_2].push_back(rook(position(4, 3), PLAYER_2));
    player_rooks[PLAYER_2].push_back(rook(position(3, 0), PLAYER_2));
    player_rooks[PLAYER_2].push_back(rook(position(1, 0), PLAYER_2));
    player_rooks[PLAYER_2].push_back(rook(position(4, 5), PLAYER_2));
    player_rooks[PLAYER_2].push_back(rook(position(4, 4), PLAYER_2));
    player_bishops[PLAYER_2].push_back(bishop(position(0, 7), PLAYER_2));

    board_matrix[make_index_8(2, 4)] = &player_king[PLAYER_1][0];
    board_matrix[make_index_8(4, 3)] = &player_rooks[PLAYER_2][0];
    board_matrix[make_index_8(3, 0)] = &player_rooks[PLAYER_2][1];
    board_matrix[make_index_8(1, 0)] = &player_rooks[PLAYER_2][2];
    board_matrix[make_index_8(4, 5)] = &player_rooks[PLAYER_2][3];
    board_matrix[make_index_8(4, 4)] = &player_rooks[PLAYER_2][4];
    board_matrix[make_index_8(0, 7)] = &player_bishops[PLAYER_2][0];

    //move_piece(position(3, 0), position(2, 0));


}


/*
    Setup 6:
     01234567
    0///////A
    1////////
    2////r///
    3T///////
    4///T/T//
    5////////
    6////////
    7////////

    Test: Verificare la condizione di scacco matto.
*/
void board::setup_6()
{
    player_king[PLAYER_1].push_back(king(position(2, 4), PLAYER_1));

    player_rooks[PLAYER_2].push_back(rook(position(4, 3), PLAYER_2));
    player_rooks[PLAYER_2].push_back(rook(position(3, 0), PLAYER_2));
    player_rooks[PLAYER_2].push_back(rook(position(4, 5), PLAYER_2));
    //player_rooks[PLAYER_2].push_back(rook(position(4, 4), PLAYER_2));
    player_bishops[PLAYER_2].push_back(bishop(position(0, 7), PLAYER_2));

    board_matrix[make_index_8(2, 4)] = &player_king[PLAYER_1][0];
    board_matrix[make_index_8(4, 3)] = &player_rooks[PLAYER_2][0];
    board_matrix[make_index_8(3, 0)] = &player_rooks[PLAYER_2][1];
    board_matrix[make_index_8(4, 5)] = &player_rooks[PLAYER_2][2];
    //board_matrix[make_index_8(4, 4)] = &player_rooks[PLAYER_2][3];
    board_matrix[make_index_8(0, 7)] = &player_bishops[PLAYER_2][0];

    //move_piece(position(3, 0), position(2, 0));


}

bool board::move_piece(const position& from, const position& to)
{
    if (board_matrix[make_index_8(from)] == nullptr)   // non c'è una pedina nella casella from
    {
        return false; // da def, forse eccezione o altro
    }

    piece* p = board_matrix[make_index_8(from)];

    /*
    if (condizione di en passant)
        en_passant();

    if (condizione di arrocco)
        arrocco();
    
    */

    // ----------------------- Sezione mossa normale -----------------------
    if (p->can_move_to(to, board_matrix) || p->can_capture(to, board_matrix))   //migliora
    {
        // Pezzo sulla scacchiera sulla posizione di destinazione (eventualmente anche nullptr)
        piece* prev_in_dest{board_matrix[make_index_8(to)]};

        p->set_position(to);
        board_matrix[make_index_8(to)] = p;
        board_matrix[make_index_8(from)] = nullptr;

        // Se dopo una propria mossa si ha una situazione di check allora la mossa non è valida.
        if (is_check(p->get_player()))
        {
            // Ritorna alla situazione iniziale
            board_matrix[make_index_8(from)] = p;
            p->set_position(from);
            board_matrix[make_index_8(to)] = prev_in_dest;
            cout << "Mossa non valida. La mossa porta ad uno scacco del proprio re.\n";
            return false;
        }
        
        /*
        if (può_promuovere)
            promuovi();
        */

        // Mossa lecita
        return true;
    }
    else    // Allora la destinazione non è nelle possibili posizioni.
    {
        cout << "Mossa non valida. Da " << from << " a " << to << endl;
        return false;
    }
    
}

/*bool board::move_piece_2(const position& from, const position& to)
{
    if (board_matrix[make_index_8(from)] == nullptr)   // non c'è una pedina nella casella from
    {
        return false; // da def, forse eccezione o altro
    }

    piece* p = board_matrix[make_index_8(from)];
    if (p->can_move_to(to, board_matrix) || p->can_capture(to, board_matrix))   //migliora
    {
        // MOMENTANEO WORK IN PROGRESS
        // aggiornare posizione in p

        p->set_position(to);
        board_matrix[make_index_8(to)] = p;
        board_matrix[make_index_8(from)] = nullptr;
        //p->move(position(to));
        return true;
    }
    else
    {
        //cout << "Mossa non valida. Da " << from << " a " << to << endl;
        return false;
    }
    
}
*/

bool board::is_check(int player_number)
{
    return player_king[player_number].front().is_check(board_matrix);

    /*int other = player_number == PLAYER_1 ? PLAYER_2 : PLAYER_1;    // ottengo l'altro player
    king player_number_king = player_king[player_number].front();
    position king_pos{player_number_king.get_position()};

    for (auto p : board_matrix)
    {
        //std::cout << "Checking if " << p->symbol() << " can check king.\n";
        if (p && (p->get_player() != player_number && p->can_capture(king_pos, board_matrix)))
        {
            std::cout << "Piece " << p->symbol() << " checks king.\n";
            return true;
        }
        //std::cout << "Cannot check king.\n";
    }
    std::cout << "No check mate.\n";
    return false;
    */
}

bool board::is_checkmate(int player_number)
{
    // Per ogni pezzo della board
    for (auto p : board_matrix)
    {
        // Il puntatore deve essere valido ed avere numero di giocatore uguale a player_number
        if (!p || p->get_player() != player_number)
            continue;

        // Per ogni possibile posizione del pezzo
        for (auto dest : p->get_possible_positions())
        {
            // Controlla se può raggiungere tale posizione
            if (!p->can_move_to(dest, board_matrix) && !p->can_capture(dest, board_matrix))
                continue;
            
            
            // Mossa fittizia
            piece* prev_in_dest = board_matrix[make_index_8(dest)];
            position prev_p_pos = p->get_position();

            board_matrix[make_index_8(dest)] = p;
            board_matrix[make_index_8(p->get_position())] = nullptr;
            p->set_position(dest);

            // Controllo se in tale configurazione è scaco
            bool is_check_bool = is_check(player_number);

            // debug
            print_board();
            if (is_check(player_number))
            {
                cout << "check\n";
            }
            else
            {
                cout << "NOT check\n";
            }

            // Ripristino della configurazione iniziale
            board_matrix[make_index_8(dest)] = prev_in_dest;
            board_matrix[make_index_8(prev_p_pos)] = p;
            p->set_position(prev_p_pos);

            // Se eseguendo tale mossa non vi è più lo scacco al re allora non è scacco matto
            if (!is_check_bool)
                return false;

        }
    }

    // Altrimenti è necessariamente scacco matto
    return true;
}

bool board::is_checkmate2(int player_number)
{
    /*
        Controllo se il re, muovendosi, può risolvere la situazione
        di scacco.
    */
    
    king k = player_king[player_number].front();
    position k_pos{k.get_position()};
    vector<position> king_possible_positions = k.get_possible_positions();
    
    for (auto dest : king_possible_positions)
    {
        
        cout << "---------------------------\n";
        cout << "move: " << dest << endl;
        
        bool can_escape_this_way = true;

        if (!k.can_move_to(dest, board_matrix))
        {
            continue;
        }

        // Mossa fittizia
        piece* prev_in_dest = board_matrix[make_index_8(dest)];
        board_matrix[make_index_8(dest)] = &k;
        board_matrix[make_index_8(k_pos)] = nullptr;

        print_board();

        // Per ogni pezzo della board
        for (auto p : board_matrix)
        {
            if (!p || p->get_player() == k.get_player()) continue;

            cout << "Can " << p->symbol() << p->get_position() << " eat king?\n";
            if (p->can_capture(dest, board_matrix))
            {
                can_escape_this_way = false;
                cout << "Yes.\n";
            }
            else
            {
                cout << "No.\n";
            }
        }

        board_matrix[make_index_8(k_pos)] = &k;
        board_matrix[make_index_8(dest)] = prev_in_dest;

        if (can_escape_this_way)
        {
            return false;
        }
    }

    /*
        A questo il punto allora il re, muovendosi, non può risolvere la situazione
        di scacco. E' necessario controllare se muovendo qualunque altra dello
        stesso colore del re sotto scacco si riesce a risolvere lo scacco.
    */



    return true;
}

void board::to_empty()
{
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            board_matrix[make_index_8(i, j)] = nullptr;
        }
    }
}

void board::init_board()
{
    board_matrix.resize(board_size * board_size);

    // King
    player_king[PLAYER_1].reserve(piece_numbers::king_number);
    player_king[PLAYER_2].reserve(piece_numbers::king_number);
    // Knights
    player_knights[PLAYER_1].reserve(piece_numbers::knight_number);
    player_knights[PLAYER_2].reserve(piece_numbers::knight_number);
    // Bishops
    player_bishops[PLAYER_1].reserve(piece_numbers::bishop_number);
    player_bishops[PLAYER_2].reserve(piece_numbers::bishop_number);
    // Pawns
    player_pawns[PLAYER_1].reserve(piece_numbers::pawn_number);
    player_pawns[PLAYER_2].reserve(piece_numbers::pawn_number);
    // Rooks
    player_rooks[PLAYER_1].reserve(piece_numbers::rook_number);
    player_rooks[PLAYER_2].reserve(piece_numbers::rook_number);
    // Queens
    player_queen[PLAYER_1].reserve(piece_numbers::queen_number + piece_numbers::pawn_number);
    player_queen[PLAYER_2].reserve(piece_numbers::queen_number + piece_numbers::pawn_number);
    
    to_empty();
}

std::vector<position> board::get_player_pieces_positions(int player)
{
    vector<position> player_pieces_positions;
    
    // Scan di tutti i contenitori relativi ai pezzi del player
    
    // Scan dei pawns
    for (pawn p : player_pawns[player])
    {
        player_pieces_positions.push_back(p.get_position());
    }
    // Scan dei knight
    for (knight p : player_knights[player])
    {
        player_pieces_positions.push_back(p.get_position());
    }
    // Scan dei bishop
    for (bishop p : player_bishops[player])
    {
        player_pieces_positions.push_back(p.get_position());
    }
    // Scan dei king
    for (king p : player_king[player])
    {
        player_pieces_positions.push_back(p.get_position());
    }
    // Scan dei queen
    for (queen p : player_queen[player])
    {
        player_pieces_positions.push_back(p.get_position());
    }
    // Scan dei rook
    for (rook p : player_rooks[player])
    {
        player_pieces_positions.push_back(p.get_position());
    }

    return player_pieces_positions;

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

    for (int i = 0; i < piece_numbers::pawn_number; i++)
    {
        player_pawns[PLAYER_1].push_back(pawn(position(PAWN_ROW_PLAYER_1, i), PLAYER_1));
        player_pawns[PLAYER_2].push_back(pawn(position(PAWN_ROW_PLAYER_2, i), PLAYER_2));
        
    }
    for (int i = 0; i < piece_numbers::pawn_number; i++)
    {
        //board_matrix[PAWN_ROW_PLAYER_2][i] = &player_pawns[PLAYER_2][i];
        //board_matrix[PAWN_ROW_PLAYER_1][i] = &player_pawns[PLAYER_1][i];

        board_matrix[make_index_8(PAWN_ROW_PLAYER_2, i)] = &player_pawns[PLAYER_2][i];
        board_matrix[make_index_8(PAWN_ROW_PLAYER_1, i)] = &player_pawns[PLAYER_1][i];
    }


    // ----------- Inserimento knights ----------- 

    player_knights[PLAYER_1].push_back(knight(position(7, 1), PLAYER_1));
    player_knights[PLAYER_2].push_back(knight(position(0, 1), PLAYER_2));
    player_knights[PLAYER_1].push_back(knight(position(7, 6), PLAYER_1));
    player_knights[PLAYER_2].push_back(knight(position(0, 6), PLAYER_2));
    
    /*board_matrix[7][1] = &player_knights[PLAYER_1][0];
    board_matrix[0][1] = &player_knights[PLAYER_2][0];
    board_matrix[7][6] = &player_knights[PLAYER_1][1];
    board_matrix[0][6] = &player_knights[PLAYER_2][1]; 
    */
    board_matrix[make_index_8(7, 1)] = &player_knights[PLAYER_1][0];
    board_matrix[make_index_8(0, 1)] = &player_knights[PLAYER_2][0];
    board_matrix[make_index_8(7, 6)] = &player_knights[PLAYER_1][1];
    board_matrix[make_index_8(0, 6)] = &player_knights[PLAYER_2][1]; 

    // ----------- Inserimento bishop ----------- 

    player_bishops[PLAYER_1].push_back(bishop(position(7, 2), PLAYER_1));
    player_bishops[PLAYER_2].push_back(bishop(position(0, 2), PLAYER_2));
    player_bishops[PLAYER_1].push_back(bishop(position(7, 5), PLAYER_1));
    player_bishops[PLAYER_2].push_back(bishop(position(0, 5), PLAYER_2));
    
    board_matrix[make_index_8(7, 2)] = &player_bishops[PLAYER_1][0];
    board_matrix[make_index_8(0, 2)] = &player_bishops[PLAYER_2][0];
    board_matrix[make_index_8(7, 5)] = &player_bishops[PLAYER_1][1];
    board_matrix[make_index_8(0, 5)] = &player_bishops[PLAYER_2][1];

    // ----------- Inserimento rook ----------- 

    player_rooks[PLAYER_1].push_back(rook(position(7, 0), PLAYER_1));
    player_rooks[PLAYER_2].push_back(rook(position(0, 0), PLAYER_2));
    player_rooks[PLAYER_1].push_back(rook(position(7, 7), PLAYER_1));
    player_rooks[PLAYER_2].push_back(rook(position(0, 7), PLAYER_2));
    
    /*board_matrix[7][0] = &player_rooks[PLAYER_1][0];
    board_matrix[0][0] = &player_rooks[PLAYER_2][0];
    board_matrix[7][7] = &player_rooks[PLAYER_1][1];
    board_matrix[0][7] = &player_rooks[PLAYER_2][1];
    */
    board_matrix[make_index_8(7, 0)] = &player_rooks[PLAYER_1][0];
    board_matrix[make_index_8(0, 0)] = &player_rooks[PLAYER_2][0];
    board_matrix[make_index_8(7, 7)] = &player_rooks[PLAYER_1][1];
    board_matrix[make_index_8(0, 7)] = &player_rooks[PLAYER_2][1];

    // ----------- Inserimento queen -----------

    player_queen[PLAYER_1].push_back(queen(position(7, 3), PLAYER_1));
    player_queen[PLAYER_2].push_back(queen(position(0, 3), PLAYER_2));

    board_matrix[make_index_8(0, 3)] = &player_queen[PLAYER_2][0];
    board_matrix[make_index_8(7, 3)] = &player_queen[PLAYER_1][0];

    // ----------- Inserimento king -----------

    player_king[PLAYER_1].push_back(king(position(7, 4), PLAYER_1));
    player_king[PLAYER_2].push_back(king(position(0, 4), PLAYER_2));

    board_matrix[make_index_8(7, 4)] = &player_king[PLAYER_1][0];
    board_matrix[make_index_8(0, 4)] = &player_king[PLAYER_2][0];

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
           piece* p = board_matrix[make_index_8(i, j)];
           if (p == nullptr)
           {
               std::cout << "/";
           }
           else
           {
               std::cout << p->symbol();
               //std::cout << p->get_position();
               //std::cout << "*";
           }
           
       }
       std::cout << std::endl;
   }
   std::cout << "  ABCDEFGH\n";

}

void board::file_print_board(ofstream& _out_file){
    for (int i = 0; i < board_size; i++){
        _out_file << board_size - i << " ";
        for (int j = 0; j < board_size; j++){
            piece* p = board_matrix[make_index_8(i, j)];
            if (p == nullptr){
                _out_file << "/";
            } else {
                _out_file << p->symbol();
            }
        }
        _out_file << std::endl;
    }
    _out_file << "  ABCDEFGH\n";
}