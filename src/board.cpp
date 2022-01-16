// Author: NICOLA MARITAN

#include "board.h"

#include <algorithm>
#include <vector>

using namespace std;

board::board()
{
    init_board();
    //setup_9();
    init_player_pieces();
}

// Copy constructor
board::board(const board& other)
{
    init_board();
    for (piece* p : other.board_matrix)
    {
        if(!p)  continue;

        if (is_pawn(p))
            insert_pawn(p->get_position(), p->get_player());
        else if (is_king(p))
            insert_king(p->get_position(), p->get_player());
        else if (is_queen(p))
            insert_queen(p->get_position(), p->get_player());
        else if (is_rook(p))
            insert_rook(p->get_position(), p->get_player());
        else if (is_knight(p))
            insert_knight(p->get_position(), p->get_player());
        else if (is_bishop(p))
            insert_bishop(p->get_position(), p->get_player());  
    }
}

// Copy assignment
board board::operator=(const board& other)
{
    // Copia dei piece
    vector<pawn> new_p_pawns_1 = other.player_pawns[player_1];
    vector<pawn> new_p_pawns_2 = other.player_pawns[player_2];
    vector<bishop> new_p_bishops_1 = other.player_bishops[player_1];
    vector<bishop> new_p_bishops_2 = other.player_bishops[player_2];
    vector<king> new_p_king_1 = other.player_king[player_1];
    vector<king> new_p_king_2 = other.player_king[player_2];
    vector<queen> new_p_queen_1 = other.player_queen[player_1];
    vector<queen> new_p_queen_2 = other.player_queen[player_2];
    vector<rook> new_p_rook_1 = other.player_rooks[player_1];
    vector<rook> new_p_rook_2 = other.player_rooks[player_2];
    vector<knight> new_p_knight_1 = other.player_knights[player_1];
    vector<knight> new_p_knight_2 = other.player_knights[player_2];

    // Solo una volta effettuata la copia posso eliminare (gestione caso in cui other == this)
    player_pawns[player_1].clear();
    player_pawns[player_2].clear();
    player_bishops[player_1].clear();
    player_bishops[player_2].clear();
    player_king[player_1].clear();
    player_king[player_2].clear();
    player_queen[player_1].clear();
    player_queen[player_2].clear();
    player_rooks[player_1].clear();
    player_rooks[player_2].clear();
    player_knights[player_1].clear();
    player_knights[player_2].clear();

    //cout << "cleared.\n";

    init_board();
    
    // Inserisco i pezzi copiati nei vector
    // Pawn
    for (pawn p : new_p_pawns_1)
    {
        insert_pawn(p.get_position(), p.get_player());
    }
    for (pawn p : new_p_pawns_2)
    {
        insert_pawn(p.get_position(), p.get_player());
    }
    //cout << "pawns inserted.\n";
    // Rook
    for (rook p : new_p_rook_1)
    {
        insert_rook(p.get_position(), p.get_player());
    }
    for (rook p : new_p_rook_2)
    {
        insert_rook(p.get_position(), p.get_player());
    }
    //cout << "rook inserted.\n";
    // King
    for (king p : new_p_king_1)
    {
        insert_king(p.get_position(), p.get_player());
    }
    for (king p : new_p_king_2)
    {
        insert_king(p.get_position(), p.get_player());
    }
    //cout << "king inserted.\n";
    // Queen
    for (queen p : new_p_queen_1)
    {
        insert_queen(p.get_position(), p.get_player());
    }
    for (queen p : new_p_queen_2)
    {
        insert_queen(p.get_position(), p.get_player());
    }
    //cout << "queen inserted.\n";
    // Bishops
    for (bishop p : new_p_bishops_1)
    {
        insert_bishop(p.get_position(), p.get_player());
    }
    for (bishop p : new_p_bishops_2)
    {
        insert_bishop(p.get_position(), p.get_player());
    }
    //cout << "bishops inserted.\n";
    // Knight
    for (knight p : new_p_knight_1)
    {
        insert_knight(p.get_position(), p.get_player());
    }
    for (knight p : new_p_knight_2)
    {
        insert_knight(p.get_position(), p.get_player());
    }
    //cout << "knight inserted.\n";

    return *this;
}

/*
    La funzione membro move_piece rappresenta l'interfaccia fra il player 
    e la board concreta. Essa chiama per un determinato pezzo le funzioni 
    membro virtuali can_move_to, can_capture, ecc. di piece. 
    Essa modifica concretamente la board. Funzione membro CHIAVE della board che muove fisicamente il pezzo.
*/
bool board::move_piece(const position& from, const position& to)
{
    /*try
    {
        cout << "Call a move_piece; from : " << get_string_8(from) << "; to: " << get_string_8(to) << endl;
    }
    catch(const bad_position_8)
    {
        std::cerr << "bad_position in move_piece. returning false." << '\n';
        //return false;
    }*/
    
    
    // Se la posizione di partenza viene chiamata una eccezione, errore grave
    if (!is_valid_position_8(from)) throw bad_position_8();
    // Provare a muovere un pezzo da una posizione valida a una non comporta "solo" che la funzione restituisca false
    if (!is_valid_position_8(to)) return false;

    if(is_draw(board_matrix.at(make_index_8(from))->get_player()))
    {
        return false;
    }

    if (board_matrix.at(make_index_8(from)) == nullptr)   // Non c'è una pedina nella casella from
    {
        return false; // Restituisce false
    }

    // Pezzo sulla scacchiera sulla posizione di destinazione (eventualmente anche nullptr)
    piece* prev_in_dest = board_matrix.at(make_index_8(to));
    piece* p = board_matrix.at(make_index_8(from));

    // Se non è un pedone oppure non può fare l'en passant
    if(!is_pawn(p) || !can_en_passant(from, to))
    {
        // 
        for(int i = 0; i < player_pawns[p->get_player()].size(); i++)
        {
            (player_pawns[p->get_player()].at(i)).set_can_be_passed(false);
        }
    }

    // ----------------- Arrocco -----------------
    if(is_king(p) && !is_check(p->get_player()) && is_castling(from, to))
    //if (false)
    {
        //cout << "is_castling true\n";
        piece* _king = board_matrix.at(make_index_8(from));
        piece* _rook;

        /*if(is_check(_king->get_player()))
            return false;
        */
        
        position rook_from; // Posizione di partenza della torre
        position rook_to;   // Sua posizione di arrivo
        if(from.col > to.col) // va a sinistra
        {
            rook_from = position(from.row, 0);
            rook_to = position(from.row, to.col + 1);
            _rook = board_matrix.at(make_index_8(rook_from));

            if (!_rook) return false;   // Controllo che sia un rif. valido

            if(!_rook->get_init_pos() && !_king->get_init_pos()){   // Se torre e re NON sono entrambi nella posizione iniziale
                return false;
            }

            /*
                Controllo che tra tra la torre e il re
                non ci sia nessun pezzo. Se ci sono pezzi
                allora non è possibile eseguire l'arrocco.
            */
            for(int i = 1; i < from.col; i++)
            {
                if(board_matrix.at(make_index_8(from.row,i)))
                    return false;
            }

            // Inizio di una mossa fittizia
            position temp_pos = position(from.row, from.col - 1);
            piece* prev_in_dest{board_matrix.at(make_index_8(temp_pos))};
            _king->set_position(temp_pos);
            board_matrix.at(make_index_8(temp_pos)) = _king;
            board_matrix.at(make_index_8(from)) = nullptr;
            
            /*
                Controllo se nella posizione intermedia c'è scacco al re:
                non ci può essere scacco al re in tale posizione.
            */
            if (is_check(_king->get_player()))
            {
                board_matrix.at(make_index_8(from)) = _king;
                _king->set_position(from);
                board_matrix.at(make_index_8(temp_pos)) = prev_in_dest;
                return false;
            }
            /*
                Ritorno in ogni caso alla posizione inizale, in quanto
                quello precedente era solo un controllo momentaneo
                necessario.
            */
            board_matrix.at(make_index_8(from)) = _king;
            _king->set_position(from);
            board_matrix.at(make_index_8(temp_pos)) = prev_in_dest;
        }
        else // va a destra
        {
            // Ragionamento ANALOGO a ciò che avviene nel movimento verso sinistra.
            rook_from = position(from.row, 7);
            rook_to = position(from.row, to.col - 1);
            _rook = board_matrix.at(make_index_8(rook_from));

            if (!_rook) return false;

            if(!_rook->get_init_pos() && !_king->get_init_pos()){
                return false;
            }
            for(int i = from.col + 1 ; i < 7; i++){
                if(board_matrix.at(make_index_8(from.row,i)))
                    return false;
            }
            position temp_pos = position(from.row, from.col + 1);
            piece* prev_in_dest{board_matrix.at(make_index_8(temp_pos))};
            _king->set_position(temp_pos);
            board_matrix.at(make_index_8(temp_pos)) = _king;
            board_matrix.at(make_index_8(from)) = nullptr;
            if (is_check(_king->get_player()))
            {
                board_matrix.at(make_index_8(from)) = _king;
                _king->set_position(from);
                board_matrix.at(make_index_8(temp_pos)) = prev_in_dest;
                return false;
            }
            board_matrix.at(make_index_8(from)) = _king;
            _king->set_position(from);
            board_matrix.at(make_index_8(temp_pos)) = prev_in_dest;
        }

        // CONTROLLO CHE NELLA DESTINAZIONE IL RE NON VADA IN SCACCO ALTRIMENTI ESEGUO L' ARROCCO DEL RE
        // Controllo che il re nella nuova posizione non sia sotto scacco.
        piece* prev_in_dest = board_matrix.at(make_index_8(to));
        _king->set_position(to);
        board_matrix.at(make_index_8(to)) = _king;
        board_matrix.at(make_index_8(from)) = nullptr;
        if (is_check(_king->get_player()))
        {   
            board_matrix.at(make_index_8(from)) = _king;
            _king->set_position(from);
            board_matrix.at(make_index_8(to)) = prev_in_dest;
            return false;
        }
        
        // ESEGUO L' ARROCCO DELLA TORRE
        _rook->set_position(rook_to);
        board_matrix.at(make_index_8(rook_to)) = _rook;
        board_matrix.at(make_index_8(rook_from)) = nullptr;

        // TO DO: Set initial position to false
        //_rook->set_init_pos();
        //_king->set_init_pos();

        _rook->set_init_pos();
        _king->set_init_pos();

        count_draw++;
        states[all_board_symbols()]++;
        log.push_back(get_string_8(from) + " " + get_string_8(to));
        return true;
    }

    // ----------------- En passant -----------------
    // N.B.! Nella posizione to, in caso di en passant, e' impossibile che vi sia una pedina; 
    // se fosse il contrario, il pedone avversario non avrebbe potuto fare 2 passi (nemmeno uno in realta')
    if(can_en_passant(from, to))
    {
        int sign = p->get_player() == player_id::player_1 ? -1 : 1;  // orientazione
        position pos_to_pass = to - position(sign, 0);

        // Pezzo sulla scacchiera sulla posizione di destinazione (eventualmente anche nullptr)
        prev_in_dest = board_matrix.at(make_index_8(pos_to_pass));

        p->set_position(to);
        board_matrix.at(make_index_8(to)) = p;
        board_matrix.at(make_index_8(from)) = nullptr;
        board_matrix.at(make_index_8(pos_to_pass)) = nullptr;

        // Se dopo una propria mossa si ha una situazione di check allora la mossa non è valida.
        if (is_check(p->get_player()))
        {
            board_matrix.at(make_index_8(from)) = p;// Ritorna alla situazione iniziale
            p->set_position(from);
            board_matrix.at(make_index_8(pos_to_pass)) = prev_in_dest;
            return false;
        }

        p->set_init_pos_to_false();

        count_draw++;
        states[all_board_symbols()]++;
        log.push_back(get_string_8(from) + " " + get_string_8(to));
        return true;
    }
    // Pezzo sulla scacchiera sulla posizione di destinazione (eventualmente anche nullptr)
    prev_in_dest = board_matrix.at(make_index_8(to));

    // ----------------------- Sezione mossa normale -----------------------
    if (p->can_move_to(to, board_matrix) || p->can_capture(to, board_matrix))
    {
        p->set_position(to);
        board_matrix.at(make_index_8(to)) = p;
        board_matrix.at(make_index_8(from)) = nullptr;

        // Se dopo una propria mossa si ha una situazione di check allora la mossa non è valida.
        if (is_check(p->get_player()))
        {
            board_matrix.at(make_index_8(from)) = p; // Ritorna alla situazione iniziale
            p->set_position(from);
            board_matrix.at(make_index_8(to)) = prev_in_dest;
            return false;
        }
        p->set_init_pos_to_false();
    }
    else return false;

    // -------------- Promozione -----------------
    if (p->get_player() == player_id::player_1)
    {
        constexpr int final_row{0};
        if (p->get_position().row == final_row)
        {
            promote(p->get_position());
        }
    }
    else    // se no a ze pan a ze polenta
    {
        constexpr int final_row{7};
        if (p->get_position().row == final_row)
        {
            promote(p->get_position());
        }
    }

    if(!is_pawn(p) && !prev_in_dest)
    {
        no_pwn_no_eat++;
    }

    // Mossa lecita
    count_draw++;
    states[all_board_symbols()]++;
    //cout << "state: " << all_board_symbols() << ": " << states[all_board_symbols()] << endl;
    log.push_back(get_string_8(from) + " " + get_string_8(to));
    return true;    
}

bool board::can_en_passant(const position& passing, const position& to) const
{
    piece* pce{board_matrix.at(make_index_8(passing))};

    //AGGIUNTO IN CORSO D'OPERA (ho modificato pensando di rendere il tutto piu coerente)
    int sign = pce->get_player() == player_id::player_1 ? -1 : 1;  // orientazione
    position pos_to_pass = to - position(sign, 0);

    if (!is_valid_position_8(pos_to_pass))  return false;

    piece* pce_to_pass{board_matrix.at(make_index_8(pos_to_pass))};

    if (!pce_to_pass || !pce) 
        return false;  // Non c'è una pedina in pos_to_pass

    if (is_pawn(pce))
    {
        if(pce_to_pass->get_can_be_passed() && pce_to_pass->get_player() != pce->get_player())
            return true;        
    }
    
    return false;
}

bool board::is_check(player_id player_number)
{   //Si limita a chiamare is_check del re del proprio giocatore.
    return player_king[player_number].front().is_check(board_matrix);
}

bool board::has_king_been_captured(player_id id) const
{
    for (auto p : board_matrix)
    {
        if (p && p->get_player() == id && is_king(p))
            return false;
    }
    return true;
}

/*
    Si occupa di determinare lo stato di check_mate per un determinato
    giocatore. Se ogni mossa possibile del giocare non risolve la situazione
    di scacco, allora è necessariamente scacco matto. Se esiste anche solamente
    una mossa che lo evita allora restituisce false.
*/
bool board::is_checkmate(player_id player_number)
{
    //cout << "Call a check mate.\n";
    for (auto p : board_matrix) // Per ogni pezzo della board
    {
        // Il puntatore deve essere valido ed avere numero di giocatore uguale a player_number
        if (!p || p->get_player() != player_number)
            continue;

        for (auto dest : p->get_possible_positions()) // Per ogni possibile posizione del pezzo
        {
            // Controlla se può raggiungere tale posizione
            if (!p->can_move_to(dest, board_matrix) && !p->can_capture(dest, board_matrix)) continue;

            // Mossa fittizia
            piece* prev_in_dest = board_matrix.at(make_index_8(dest));
            position prev_p_pos = p->get_position();

            board_matrix.at(make_index_8(dest)) = p;
            board_matrix.at(make_index_8(p->get_position())) = nullptr;
            p->set_position(dest);

            bool is_check_bool = is_check(player_number); // Controllo se in tale configurazione è scaco

            // Ripristino della configurazione iniziale
            board_matrix.at(make_index_8(dest)) = prev_in_dest;
            board_matrix.at(make_index_8(prev_p_pos)) = p;
            p->set_position(prev_p_pos);

            if (!is_check_bool) // Se eseguendo tale mossa non vi è più lo scacco, allora non è scacco matto
            {   
                //cout << "NO check mate.\n"; 
                return false;
            }
        }
    }
    //cout << "YES check mate.\n"; 
    return true; // Altrimenti è necessariamente scacco matto
}


bool board::is_castling(const position& from, const position& to) const
{
    const position king_start_1(7, 4);
    const position king_start_2(0, 4);
    constexpr int col_diff{2};

    if((abs(from.col - to.col) == col_diff) && (from == king_start_1 || from == king_start_2))
    {
        return true;
    }

    return false;
}


/*
    Rende vuota la board inizializzando a nullptr ogni riferimento
    in board_matrix.
*/
void board::to_empty()
{
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            board_matrix.at(make_index_8(i, j)) = nullptr;
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
    player_king[player_id::player_1].reserve(piece_numbers::king_number);
    player_king[player_id::player_2].reserve(piece_numbers::king_number);
    // Knights
    player_knights[player_id::player_1].reserve(piece_numbers::knight_number);
    player_knights[player_id::player_2].reserve(piece_numbers::knight_number);
    // Bishops
    player_bishops[player_id::player_1].reserve(piece_numbers::bishop_number);
    player_bishops[player_id::player_2].reserve(piece_numbers::bishop_number);
    // Pawns
    player_pawns[player_id::player_1].reserve(piece_numbers::pawn_number);
    player_pawns[player_id::player_2].reserve(piece_numbers::pawn_number);
    // Rooks
    player_rooks[player_id::player_1].reserve(piece_numbers::rook_number);
    player_rooks[player_id::player_2].reserve(piece_numbers::rook_number);
    // Queens
    player_queen[player_id::player_1].reserve(piece_numbers::queen_number + piece_numbers::pawn_number);
    player_queen[player_id::player_2].reserve(piece_numbers::queen_number + piece_numbers::pawn_number);
    
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
    piece* p{board_matrix.at(make_index_8(pos))};
    if (!p) return false;

    if (is_pawn(p))
    {
        player_id player_num{p->get_player()};
        /*
            Il pezzo viene inserito nel vector dei pezzi in quanto nuovo pezzo concreto.
            Ciò NON causa la riallocazione dei vector poiché avviene il reserve della
            memoria del vector di 1 (la regina iniziale) + 8 (i pedoni iniziali, che
            possono promuovere).
        */
        player_queen[player_num].push_back(queen(p->get_position(), player_num));
        board_matrix.at(make_index_8(pos)) = &player_queen[player_num].back();
        player_queen[player_num].back().set_init_pos_to_false();
        return true;
    }
    
    return false;
}

std::vector<position> board::get_player_pieces_positions(player_id player) const
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

std::vector<position> board::get_player_in_board_pieces_positions(player_id player) const
{
    vector<position> player_in_board_pieces_positions;
    for (piece* pce : board_matrix)
    {
        if (pce && pce->get_player() == player)
        {
            player_in_board_pieces_positions.push_back(pce->get_position());
        }
    }
    return player_in_board_pieces_positions;
}

void board::insert_pawn(const position& pos, player_id id)
{
    if (!is_valid_position_8(pos))  throw bad_position_8();

    if (player_pawns[id].size() == piece_numbers::pawn_number)  throw too_many_pieces();

    player_pawns[id].push_back(pawn(pos, id));
    board_matrix.at(make_index_8(pos)) = &player_pawns[id].back();
}

void board::insert_king(const position& pos, player_id id)
{
    if (!is_valid_position_8(pos))  throw bad_position_8();

    if (player_king[id].size() == piece_numbers::king_number)  throw too_many_pieces();

    player_king[id].push_back(king(pos, id));
    board_matrix.at(make_index_8(pos)) = &player_king[id].back();
}

void board::insert_queen(const position& pos, player_id id)
{
    if (!is_valid_position_8(pos))  throw bad_position_8();

    if (player_queen[id].size() == piece_numbers::queen_number)  throw too_many_pieces();

    player_queen[id].push_back(queen(pos, id));
    board_matrix.at(make_index_8(pos)) = &player_queen[id].back();
}

void board::insert_rook(const position& pos, player_id id)
{
    if (!is_valid_position_8(pos))  throw bad_position_8();

    if (player_rooks[id].size() == piece_numbers::rook_number)  throw too_many_pieces();

    player_rooks[id].push_back(rook(pos, id));
    board_matrix.at(make_index_8(pos)) = &player_rooks[id].back();
}

void board::insert_bishop(const position& pos, player_id id)
{
    if (!is_valid_position_8(pos))  throw bad_position_8();

    if (player_bishops[id].size() == piece_numbers::bishop_number)  throw too_many_pieces();

    player_bishops[id].push_back(bishop(pos, id));
    board_matrix.at(make_index_8(pos)) = &player_bishops[id].back();
}

void board::insert_knight(const position& pos, player_id id)
{
    if (!is_valid_position_8(pos))  throw bad_position_8();

    if (player_knights[id].size() == piece_numbers::knight_number)  throw too_many_pieces();

    player_knights[id].push_back(knight(pos, id));
    board_matrix.at(make_index_8(pos)) = &player_knights[id].back();
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
        insert_pawn(position(PAWN_ROW_PLAYER_1, i), player_1);
        insert_pawn(position(PAWN_ROW_PLAYER_2, i), player_2);
    }


    // ----------- Inserimento knights ----------- 
    insert_knight(position(7, 1), player_1);
    insert_knight(position(0, 1), player_2);
    insert_knight(position(7, 6), player_1);
    insert_knight(position(0, 6), player_2);

    // ----------- Inserimento bishop ----------- 
    insert_bishop(position(7, 2), player_1);
    insert_bishop(position(0, 2), player_2);
    insert_bishop(position(7, 5), player_1);
    insert_bishop(position(0, 5), player_2);

    // ----------- Inserimento rook ----------- 
    insert_rook(position(7, 0), player_1);
    insert_rook(position(0, 0), player_2);
    insert_rook(position(7, 7), player_1);
    insert_rook(position(0, 7), player_2);

    // ----------- Inserimento queen -----------
    insert_queen(position(7, 3), player_1);
    insert_queen(position(0, 3), player_2);

    // ----------- Inserimento king -----------
    insert_king(position(7, 4), player_1);
    insert_king(position(0, 4), player_2);
    
}

void board::print_board() const
{
    for (int i = 0; i < board_size; i++)
    {
       cout << board_size - i << " " << row_symbols(i) << endl;
    }
    cout << "  ABCDEFGH" << endl;
}

void board::file_print_board(ofstream& _out_file)
{
    for (int i = 0; i < board_size; i++)
    {
       _out_file << board_size - i << " " << row_symbols(i) << endl;
    }
    _out_file << "  ABCDEFGH" << endl;
}

/*
Mi restituisce una stringa con i simboli della riga i della board (compresi gli spazi)
*/
string board::row_symbols(int i) const
{
    string str_board;

    for (int j = 0; j < board_size; j++)
    {
        piece* p = board_matrix.at(make_index_8(i, j));
        if (!p)
        {
           str_board += " ";
        }
        else{
           str_board += p->symbol();
        } 
    }
    return str_board;
}

string board::all_board_symbols() const
{
    string all_symbols;
    for(int i = 0; i < board_size; i++)
    {
        all_symbols += row_symbols(i);
    }
    return all_symbols;
}

/*
    La funzione is_draw ci permette di sapere se, prima della prossima mossa, si e' in una condizione in cui e' possibile procedere con la patta, ovvero interrompere la partita (in parita') per scelta o per evitare di continuare a giocare all'infinito
*/
bool board::is_draw(player_id pl)
{
    // --------------- mancanza di movimenti del pedone e di catture ---------------
    constexpr int limit {50};
    constexpr int reps_limit {3};
    if(get_no_pwn_no_eat() == limit)
    {
        cout << "Nessun pedone è stato mosso e nessuna cattura è avvenuta per " << limit << " mosse." << endl;
        return true;
    }

    // --------------- patta per mancanza di mosse possibili del player pl ---------------
    piece* p;
    vector<position> possible_pos;

    if (!is_check(pl) && !can_do_legal_move(pl))
        return true;

    //_out_file << to_string_move(from, to) << endl;

    // --------------- Controllo se è presente una configurazione avvenuta per 3 volte ---------------
    constexpr int max_state_app{3};

    // Chiamo funzione find_if con predicato una lambda expression che ritorna true se trova una ricorrenza comparsa per 3 volte.
    auto it = find_if(states.begin(), states.end(), [max_state_app](const std::pair<string, int>& p) -> bool {return p.second == max_state_app;});
    if (it != states.end())
    {
        cout << "Medesima configurazione avvenuta per " << max_state_app << " volte.\n";
        return true;
    }
    
    return false;
}

bool board::can_do_legal_move(player_id pl) const
{
    // Per ogni pedina
    for (auto p : board_matrix)
    {
        // Se non c'è alcuna pedina o se tale non è del player
        if (!p || p->get_player() != pl) continue;
        
        vector<position> possible_pos;
        possible_pos = p->get_possible_positions();
        for (auto pos : possible_pos)
        {
            // Se la pedina può muoversi verso tale posizione allora ritorna true
            if (p->can_move_to(pos, board_matrix)) return true;
        }
    }

    // Altrimenti: nessuna mossa legale.
    return false;
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
    player_bishops[player_id::player_2].push_back(bishop(position(0, 2), player_id::player_2));
    player_rooks[player_id::player_2].push_back(rook(position(0, 4), player_id::player_2));
    player_king[player_id::player_1].push_back(king(position(2, 4), player_id::player_1));
    player_bishops[player_id::player_2].push_back(bishop(position(0, 6), player_id::player_2));
    player_rooks[player_id::player_2].push_back(rook(position(2, 7), player_id::player_2));


    board_matrix.at(make_index_8(0, 2)) = &player_bishops[player_id::player_2][0];
    board_matrix.at(make_index_8(0, 4)) = &player_rooks[player_id::player_2][0];
    board_matrix.at(make_index_8(2, 4)) = &player_king[player_id::player_1][0];
    board_matrix.at(make_index_8(0, 6)) = &player_bishops[player_id::player_2][1];
    board_matrix.at(make_index_8(2, 7)) = &player_rooks[player_id::player_2][1];

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
    player_bishops[player_id::player_2].push_back(bishop(position(0, 2), player_id::player_2));
    player_rooks[player_id::player_2].push_back(rook(position(0, 4), player_id::player_2));
    player_king[player_id::player_1].push_back(king(position(2, 4), player_id::player_1));
    player_bishops[player_id::player_2].push_back(bishop(position(0, 6), player_id::player_2));
    player_rooks[player_id::player_2].push_back(rook(position(2, 7), player_id::player_2));
    player_pawns[player_id::player_2].push_back(pawn(position(2, 3), player_id::player_2));


    board_matrix.at(make_index_8(0, 2)) = &player_bishops[player_id::player_2][0];
    board_matrix.at(make_index_8(0, 4)) = &player_rooks[player_id::player_2][0];
    board_matrix.at(make_index_8(2, 4)) = &player_king[player_id::player_1][0];
    board_matrix.at(make_index_8(0, 6)) = &player_bishops[player_id::player_2][1];
    board_matrix.at(make_index_8(2, 7)) = &player_rooks[player_id::player_2][1];
    board_matrix.at(make_index_8(2, 3)) = &player_pawns[player_id::player_2][0];
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
    player_king[player_id::player_1].push_back(king(position(2, 4), player_id::player_1));
    player_pawns[player_id::player_2].push_back(pawn(position(1, 5), player_id::player_2));

    board_matrix.at(make_index_8(2, 4)) = &player_king[player_id::player_1][0];
    board_matrix.at(make_index_8(1, 5)) = &player_pawns[player_id::player_2][0];
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
    player_king[player_id::player_1].push_back(king(position(2, 4), player_id::player_1));
    player_rooks[player_id::player_2].push_back(rook(position(0, 4), player_id::player_2));
    player_bishops[player_id::player_1].push_back(bishop(position(2, 6), player_id::player_1));

    board_matrix.at(make_index_8(2, 4)) = &player_king[player_id::player_1][0];
    board_matrix.at(make_index_8(0, 4)) = &player_rooks[player_id::player_2][0];
    board_matrix.at(make_index_8(2, 6)) = & player_bishops[player_id::player_1][0];
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
    player_king[player_id::player_1].push_back(king(position(2, 4), player_id::player_1));

    player_rooks[player_id::player_2].push_back(rook(position(4, 3), player_id::player_2));
    player_rooks[player_id::player_2].push_back(rook(position(3, 0), player_id::player_2));
    player_rooks[player_id::player_2].push_back(rook(position(1, 0), player_id::player_2));
    player_rooks[player_id::player_2].push_back(rook(position(4, 5), player_id::player_2));
    player_rooks[player_id::player_2].push_back(rook(position(4, 4), player_id::player_2));
    player_bishops[player_id::player_2].push_back(bishop(position(0, 7), player_id::player_2));

    board_matrix.at(make_index_8(2, 4)) = &player_king[player_id::player_1][0];
    board_matrix.at(make_index_8(4, 3)) = &player_rooks[player_id::player_2][0];
    board_matrix.at(make_index_8(3, 0)) = &player_rooks[player_id::player_2][1];
    board_matrix.at(make_index_8(1, 0)) = &player_rooks[player_id::player_2][2];
    board_matrix.at(make_index_8(4, 5)) = &player_rooks[player_id::player_2][3];
    board_matrix.at(make_index_8(4, 4)) = &player_rooks[player_id::player_2][4];
    board_matrix.at(make_index_8(0, 7)) = &player_bishops[player_id::player_2][0];

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
    player_king[player_id::player_1].push_back(king(position(2, 4), player_id::player_1));

    player_rooks[player_id::player_2].push_back(rook(position(4, 3), player_id::player_2));
    player_rooks[player_id::player_2].push_back(rook(position(3, 0), player_id::player_2));
    player_rooks[player_id::player_2].push_back(rook(position(4, 5), player_id::player_2));
    //player_rooks[PLAYER_2].push_back(rook(position(4, 4), PLAYER_2));
    player_bishops[player_id::player_2].push_back(bishop(position(0, 7), player_id::player_2));

    board_matrix.at(make_index_8(2, 4)) = &player_king[player_id::player_1][0];
    board_matrix.at(make_index_8(4, 3)) = &player_rooks[player_id::player_2][0];
    board_matrix.at(make_index_8(3, 0)) = &player_rooks[player_id::player_2][1];
    board_matrix.at(make_index_8(4, 5)) = &player_rooks[player_id::player_2][2];
    //board_matrix.at(make_index_8(4, 4)) = &player_rooks[PLAYER_2][3];
    board_matrix.at(make_index_8(0, 7)) = &player_bishops[player_id::player_2][0];

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
    player_pawns[player_id::player_1].push_back(pawn(position(2, 5), player_id::player_1));
    board_matrix.at(make_index_8(position(2, 5))) = &player_pawns[player_id::player_1][0];
}

/*
    Setup 8:
     01234567
    0///////R
    1////////
    2////////
    3////////
    4////////
    5////T///
    6////////
    7///////r

    Test: Patta per config ripetuta.
*/
void board::setup_8()
{
    insert_king(position(7, 7), player_1);
    insert_king(position(0, 7), player_2);
    insert_rook(position(5, 4), player_1);
}

/*
    Setup 8:
     01234567
    0///////R
    1////////
    2////////
    3////////
    4////////
    5////////
    6////////
    7///////r

    Test: Patta per config ripetuta.
*/
void board::setup_9()
{
    insert_king(position(7, 7), player_1);
    insert_king(position(0, 7), player_2);
}