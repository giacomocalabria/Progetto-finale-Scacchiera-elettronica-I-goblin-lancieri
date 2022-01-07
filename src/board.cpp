// Author: NICOLA MARITAN

#include "board.h"
#include <vector>
#include "player_id.h"

using namespace std;


board::board()
{
    std::cout << "Board Initialization.\n";
    init_board();

    #define SETUP 1
    #if SETUP
        setup_7();
    #else
        init_player_pieces();
    #endif
    std::cout << "Board initializated.\n";
}

/*
    La funzione membro move_piece rappresenta l'interfaccia fra
    il player e la board concreta. Essa chiama per un determinato
    pezzo le funzioni membro virtuali can_move_to, can_capture, ecc
    di piece. Essa modifica concretamente la board.
*/
bool board::move_piece(const position& from, const position& to)
{
    if (board_matrix[make_index_8(from)] == nullptr)   // non c'è una pedina nella casella from
    {
        return false; // da def, forse eccezione o altro
    }

    if(is_castling(from, to)){
        piece* _king = board_matrix[make_index_8(from)];
        _king->set_position(to);
        board_matrix[make_index_8(to)] = _king;
        board_matrix[make_index_8(from)] = nullptr;
        if(from.col > to.col){
            position rook_from = position(from.row, 0);
            position rook_to = position(from.row,to.col + 1);
            piece* _rook = board_matrix[make_index_8(rook_from)];
            _rook->set_position(rook_to);
            board_matrix[make_index_8(rook_to)] = _rook;
            board_matrix[make_index_8(rook_from)] = nullptr;
        }
        else{
            position rook_from = position(from.row, 7);
            position rook_to = position(from.row, to.col - 1);
            piece* _rook = board_matrix[make_index_8(rook_from)];
            _rook->set_position(rook_to);
            board_matrix[make_index_8(rook_to)] = _rook;
            board_matrix[make_index_8(rook_from)] = nullptr;
        }
        return true;
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

//-------------------- en passant --------------------

    //metti dentro a can_en_passant !!!!
    
    piece* p = board_matrix[make_index_8(from)];

    int sign = p->get_player() == board::PLAYER_1 ? -1 : 1;  // orientazione (serve?)
    position pos_to_pass = to;
    pos_to_pass.row -= sign;     //rispetto a to, in base al player la position del piece da catturare sara' di un posto in indietro (va bene?)
    piece* to_pass = board_matrix[make_index_8(pos_to_pass)];

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
    else if(can_en_passant(p, to_pass))
    {
        board_matrix[make_index_8(pos_to_pass)] = nullptr;   //pongo a null il pedone mangiato "in passant"
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
        
        // -------------- Promozione -----------------
        if (p->get_player() == PLAYER_1)
        {
            if (p->get_position().row == 0)
            {
                promote(p->get_position());
            }
        }
        else    // se no a ze pan a ze polenta
        {
            if (p->get_position().row == 7)
            {
                promote(p->get_position());
            }
        }

        // Mossa lecita
        return true;
    }
    else    // Allora la destinazione non è nelle possibili posizioni.
    {
        cout << "Mossa non valida. Da " << from << " a " << to << endl;
        return false;
    }
}

bool board::can_en_passant(piece* pce, piece* pce_to_pass)
{
    if (pce_to_pass == nullptr)   // non c'è una pedina in pos_to_pass
    {
        return false; // da def, forse eccezione o altro
    }

    //usa is_pawn() invece di sta merda


    vector<pawn> pl_pawns = player_pawns[pce->get_player()];
    for(int i = 0; i < pl_pawns.size(); i++)         //di fatto, controllo se pce punta ad un pedone o meno...
    {
        if(pl_pawns[i].get_position() == pce->get_position())  
        {
            pawn* pw = (pawn*)pce;    //ufficiale: pce e' un pawn

            vector<pawn> pl_pawns_2 = player_pawns[pce_to_pass->get_player()];
            for(int j = 0; j < pl_pawns.size(); j++) //di fatto, controllo se pce_to_pass punta ad un pedone o meno...
            {
                if(pl_pawns_2[j].get_position() == pce_to_pass->get_position())
                {
                    pawn* pw_to_pass = (pawn*)pce_to_pass;   //ufficiale: pce_to_pass e' un pawn

                    if(pw_to_pass->get_can_be_passed())
                    {
                        return true;
                    }
                    else
                        return false;
                }
            }
            cout << "\n";

            /*position right = pw->get_position();
            right.col++;
            position left = pw->get_position();
            left.col--;*/
            //break;      //le altre iterazioni del for sono riempitive, in quanto non ci possono essere altre pedine con la stessa position di quella considerata ora
        }
    }
    return false;
}

/*
    Si limita a chiamare is_check del re del proprio giocatore.
*/
bool board::is_check(player_id player_number)
{
    return player_king[player_number].front().is_check(board_matrix);
}

/*
    Si occupa di determinare lo stato di check_mate per un determinato
    giocatore. Se ogni mossa possibile del giocare non risolve la situazione
    di scacco, allora è necessariamente scacco matto. Se esiste anche solamente
    una mossa che lo evita allora restituisce false.
*/
bool board::is_checkmate(player_id player_number)
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

// Inutile, da eliminare
/*
bool board::is_checkmate2(int player_number)
{

    
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




    return true;
}
*/

/*
    Rende vuota la board inizializzando a nullptr ogni riferimento
    in board_matrix.
*/
bool board::is_castling(const position& from, const position& to){
    piece* _king = board_matrix[make_index_8(from)];
    if(true && true && abs(from.col - to.col) != 2){ //qui devo verificare se il piece king è effettivamente un Re e che il dato re non sia già sotto scacco
    if(from == position(7, 4) || from == position(0, 4)){
        return false;
    }
    //if(!_king.is_check(board_matrix) && abs(from.col - to.col) != 2){
        return false;
    }

    position rook_from = position(from.row, 0);
    position rook_to = position(from.row, 0);
    if(from.col > to.col){
        rook_from = position(from.row, 0);
        rook_to = position(from.row,to.col + 1);
        for(int i = 1; i < from.col; i++){
            if(!board_matrix[make_index_8(from.row,i)])
                return false;
        }
                
    } else {
        rook_from = position(from.row, 7);
        rook_to = position(from.row, to.col - 1);
        for(int i = 7; i > from.col; i--){
            if(!board_matrix[make_index_8(from.row,i)])
                return false;
        }
    }
    piece* _rook = board_matrix[make_index_8(rook_from)];
    if(!_rook->get_init_pos() && !_king->get_init_pos()){
        return false;
    }

    //qui verificare che il re non vada in scacco muovendosi in ciascuna delle due caselle
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
    // Resize del vector di puntatori: chiaramente ha 64 elementi
    board_matrix.resize(board_size * board_size);

    /*
        Reserve dei vector dei pezzi, in quanto una riallocazione
        dinamica della memoria da parte di ognuno di essi in genere
        renderebbe invalidi i puntatori in board_matrix. La loro
        dimensione non è variata durante l'esecuzione.
    */
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

/*
    Promote viene chiamata quando quando una cella si ritrova
    dalla parte opposta della board, tenendo conto del colore
    del giocatore: se il pezzo può pruomovere allora viene sostituito
    da una regina.
*/
bool board::promote(const position& pos)
{
    piece* p{board_matrix[make_index_8(pos)]};
    if (!p) return false;

    if (p->can_promote())
    {
        player_id player_num{p->get_player()};
        /*
            Il pezzo viene inserito nel vector dei pezzi in quanto nuovo pezzo concreto.
            Ciò NON causa la riallocazione dei vector poiché avviene il reserve della
            memoria del vector di 1 (la regina iniziale) + 8 (i pedoni iniziali, che
            possono promuovere).
        */
        player_queen[player_num].push_back(queen(p->get_position(), player_num));
        board_matrix[make_index_8(pos)] = &player_queen[player_num].back();
        return true;
    }
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
        player_pawns[PLAYER_1].push_back(pawn(position(PAWN_ROW_PLAYER_1, i), player_id::player_1));
        player_pawns[PLAYER_2].push_back(pawn(position(PAWN_ROW_PLAYER_2, i), player_id::player_2));
        
    }
    for (int i = 0; i < piece_numbers::pawn_number; i++)
    {
        //board_matrix[PAWN_ROW_PLAYER_2][i] = &player_pawns[PLAYER_2][i];
        //board_matrix[PAWN_ROW_PLAYER_1][i] = &player_pawns[PLAYER_1][i];

        board_matrix[make_index_8(PAWN_ROW_PLAYER_2, i)] = &player_pawns[player_id::player_2][i];
        board_matrix[make_index_8(PAWN_ROW_PLAYER_1, i)] = &player_pawns[player_id::player_1][i];
    }


    // ----------- Inserimento knights ----------- 

    player_knights[PLAYER_1].push_back(knight(position(7, 1), player_id::player_1));
    player_knights[PLAYER_2].push_back(knight(position(0, 1), player_id::player_2));
    player_knights[PLAYER_1].push_back(knight(position(7, 6), player_id::player_1));
    player_knights[PLAYER_2].push_back(knight(position(0, 6), player_id::player_2));
    
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

    player_bishops[PLAYER_1].push_back(bishop(position(7, 2), player_id::player_1));
    player_bishops[PLAYER_2].push_back(bishop(position(0, 2), player_id::player_2));
    player_bishops[PLAYER_1].push_back(bishop(position(7, 5), player_id::player_1));
    player_bishops[PLAYER_2].push_back(bishop(position(0, 5), player_id::player_2));
    
    board_matrix[make_index_8(7, 2)] = &player_bishops[PLAYER_1][0];
    board_matrix[make_index_8(0, 2)] = &player_bishops[PLAYER_2][0];
    board_matrix[make_index_8(7, 5)] = &player_bishops[PLAYER_1][1];
    board_matrix[make_index_8(0, 5)] = &player_bishops[PLAYER_2][1];

    // ----------- Inserimento rook ----------- 

    player_rooks[PLAYER_1].push_back(rook(position(7, 0), player_id::player_1));
    player_rooks[PLAYER_2].push_back(rook(position(0, 0), player_id::player_2));
    player_rooks[PLAYER_1].push_back(rook(position(7, 7), player_id::player_1));
    player_rooks[PLAYER_2].push_back(rook(position(0, 7), player_id::player_2));
    
    /*board_matrix[7][0] = &player_rooks[PLAYER_1][0];
    board_matrix[0][0] = &player_rooks[PLAYER_2][0];
    board_matrix[7][7] = &player_rooks[PLAYER_1][1];
    board_matrix[0][7] = &player_rooks[PLAYER_2][1];
    */
    board_matrix[make_index_8(7, 0)] = &player_rooks[player_id::player_1][0];
    board_matrix[make_index_8(0, 0)] = &player_rooks[player_id::player_2][0];
    board_matrix[make_index_8(7, 7)] = &player_rooks[player_id::player_1][1];
    board_matrix[make_index_8(0, 7)] = &player_rooks[player_id::player_2][1];

    // ----------- Inserimento queen -----------

    player_queen[PLAYER_1].push_back(queen(position(7, 3), player_id::player_1));
    player_queen[PLAYER_2].push_back(queen(position(0, 3), player_id::player_2));

    board_matrix[make_index_8(0, 3)] = &player_queen[PLAYER_2][0];
    board_matrix[make_index_8(7, 3)] = &player_queen[PLAYER_1][0];

    // ----------- Inserimento king -----------

    player_king[PLAYER_1].push_back(king(position(7, 4), player_id::player_1));
    player_king[PLAYER_2].push_back(king(position(0, 4), player_id::player_2));

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

/*
    Setup pre impostati, utilizzati per debug. Per tale motivo
    sono funzioni membro private. Ancora non sicuro se presenti
    nella vers. finale del sorgente.
*/

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
    player_bishops[PLAYER_2].push_back(bishop(position(0, 2), player_id::player_2));
    player_rooks[PLAYER_2].push_back(rook(position(0, 4), player_id::player_2));
    player_king[PLAYER_1].push_back(king(position(2, 4), player_id::player_1));
    player_bishops[PLAYER_2].push_back(bishop(position(0, 6), player_id::player_2));
    player_rooks[PLAYER_2].push_back(rook(position(2, 7), player_id::player_2));


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
    player_bishops[PLAYER_2].push_back(bishop(position(0, 2), player_id::player_2));
    player_rooks[PLAYER_2].push_back(rook(position(0, 4), player_id::player_2));
    player_king[PLAYER_1].push_back(king(position(2, 4), player_id::player_1));
    player_bishops[PLAYER_2].push_back(bishop(position(0, 6), player_id::player_2));
    player_rooks[PLAYER_2].push_back(rook(position(2, 7), player_id::player_2));
    player_pawns[PLAYER_2].push_back(pawn(position(2, 3), player_id::player_2));


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
    player_king[PLAYER_1].push_back(king(position(2, 4), player_id::player_1));
    player_pawns[PLAYER_2].push_back(pawn(position(1, 5), player_id::player_2));

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
    player_king[PLAYER_1].push_back(king(position(2, 4), player_id::player_1));
    player_rooks[PLAYER_2].push_back(rook(position(0, 4), player_id::player_2));
    player_bishops[PLAYER_1].push_back(bishop(position(2, 6), player_id::player_1));

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
    player_king[PLAYER_1].push_back(king(position(2, 4), player_id::player_1));

    player_rooks[PLAYER_2].push_back(rook(position(4, 3), player_id::player_2));
    player_rooks[PLAYER_2].push_back(rook(position(3, 0), player_id::player_2));
    player_rooks[PLAYER_2].push_back(rook(position(1, 0), player_id::player_2));
    player_rooks[PLAYER_2].push_back(rook(position(4, 5), player_id::player_2));
    player_rooks[PLAYER_2].push_back(rook(position(4, 4), player_id::player_2));
    player_bishops[PLAYER_2].push_back(bishop(position(0, 7), player_id::player_2));

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
    player_king[PLAYER_1].push_back(king(position(2, 4), player_id::player_1));

    player_rooks[PLAYER_2].push_back(rook(position(4, 3), player_id::player_2));
    player_rooks[PLAYER_2].push_back(rook(position(3, 0), player_id::player_2));
    player_rooks[PLAYER_2].push_back(rook(position(4, 5), player_id::player_2));
    //player_rooks[PLAYER_2].push_back(rook(position(4, 4), PLAYER_2));
    player_bishops[PLAYER_2].push_back(bishop(position(0, 7), player_id::player_2));

    board_matrix[make_index_8(2, 4)] = &player_king[PLAYER_1][0];
    board_matrix[make_index_8(4, 3)] = &player_rooks[PLAYER_2][0];
    board_matrix[make_index_8(3, 0)] = &player_rooks[PLAYER_2][1];
    board_matrix[make_index_8(4, 5)] = &player_rooks[PLAYER_2][2];
    //board_matrix[make_index_8(4, 4)] = &player_rooks[PLAYER_2][3];
    board_matrix[make_index_8(0, 7)] = &player_bishops[PLAYER_2][0];

    //move_piece(position(3, 0), position(2, 0));


}


/*
    Setup 7:
     01234567
    0////////
    1////////
    2/////p//
    3////////
    4////////
    5////////
    6////////
    7////////

    Test: Verificare la promozione.
*/
void board::setup_7()
{
    player_pawns[PLAYER_1].push_back(pawn(position(2, 5), player_id::player_1));
    board_matrix[make_index_8(position(2, 5))] = &player_pawns[PLAYER_1][0];
}