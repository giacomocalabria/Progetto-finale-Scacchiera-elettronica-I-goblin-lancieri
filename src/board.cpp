// Author: NICOLA MARITAN

#include "board.h"

#include <algorithm>
#include <vector>

using namespace std;

board::board()
{
    init_board();
    init_player_pieces();
}

/*
    La funzione membro move_piece rappresenta l'interfaccia fra
    il player e la board concreta. Essa chiama per un determinato
    pezzo le funzioni membro virtuali can_move_to, can_capture, ecc
    di piece. Essa modifica concretamente la board.
*/
bool board::move_piece(const position& from, const position& to)
{
    if(is_draw(board_matrix[make_index_8(from)]->get_player()))
    {
        return false;
    }

    if (board_matrix[make_index_8(from)] == nullptr)   // Non c'è una pedina nella casella from
    {
        return false; // Restituisce false
    }
    // Se non è una posizione logicamente valida:
    if (!is_valid_position_8(from) || !is_valid_position_8(to))
    {
        return false;
    }

    // ----------------- Arrocco -----------------
    
    /*if(is_castling(from, to)){
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
        count_draw++;
        states[all_board_symbols()]++;
        
        log.push_back(get_string(from)+" "+get_string(to));
        return true;
    }*/

    piece* p = board_matrix[make_index_8(from)];


    // ----------------- En passant -----------------
    int sign = p->get_player() == board::PLAYER_1 ? -1 : 1;  // orientazione (serve?)
    position pos_to_pass = to;
    pos_to_pass.row -= sign; 
    //N.B.! Nella posizione to, in caso di en passant, e' impossibile che vi sia una pedina; se fosse il contrario, il pedone avversario non avrebbe potuto fare 2 passi (nemmeno uno in realta')

    if(can_en_passant(from, pos_to_pass))
    {
        // Pezzo sulla scacchiera sulla posizione di destinazione (eventualmente anche nullptr)
        piece* prev_in_dest{board_matrix[make_index_8(pos_to_pass)]};

        board_matrix[make_index_8(pos_to_pass)] = nullptr;   //pongo a null il pedone mangiato "in passant"
        p->set_position(to);
        board_matrix[make_index_8(to)] = p;
        board_matrix[make_index_8(from)] = nullptr;

        // AGGIUNGERE ANNULLAMENTO MOSSA SE DOPO QUESTA MOSSA IL RE E' SOTTO SCACCO(fatto)

        if(is_check(p->get_player()))
        {
            //Ritorna alla situazione iniziale
            board_matrix[make_index_8(to)] = nullptr;
            board_matrix[make_index_8(from)] = p;
            p->set_position(from);
            board_matrix[make_index_8(pos_to_pass)] = prev_in_dest;
            return false;
        }

        count_draw++;
        cout << all_board_symbols() << "ddddddddd" << std::endl;
        cout << states[all_board_symbols()];
        states[all_board_symbols()]++;
        return true;
    }


    //piece* p = board_matrix[make_index_8(from)];

    // Pezzo sulla scacchiera sulla posizione di destinazione (eventualmente anche nullptr)
    piece* prev_in_dest{board_matrix[make_index_8(to)]};


    // ----------------------- Sezione mossa normale -----------------------
    if (p->can_move_to(to, board_matrix) || p->can_capture(to, board_matrix))
    {
        p->set_position(to);
        board_matrix[make_index_8(to)] = p;
        board_matrix[make_index_8(from)] = nullptr;

        // Se dopo una propria mossa si ha una situazione di check allora la mossa non è valida.
        cout << "Chiamata a is_check.\n";
        if (is_check(p->get_player()))
        {
            // Ritorna alla situazione iniziale
            board_matrix[make_index_8(from)] = p;
            p->set_position(from);
            board_matrix[make_index_8(to)] = prev_in_dest;
            cout << "Mossa non valida. La mossa porta ad uno scacco del proprio re.\n";
            return false;
        }

    }
    else    // Allora la destinazione non è nelle possibili posizioni.
    {
        cout << "Mossa non valida. Da " << from << " a " << to << endl;
        return false;
    }
    cout << "Nessun scacco.\n";

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

    if(!p->can_promote() && !prev_in_dest)
    {
        no_pwn_no_eat++;
    }

    // Mossa lecita
    count_draw++;
    cout << all_board_symbols() << endl;
    
    /*auto iterator = find(states.begin(), states.end(), all_board_symbols());
    if(iterator == states.end())
    {
        //states[all_board_symbols()] = 0;
    }
    else
    {
        //states[all_board_symbols()]++;
    }*/
    
    //int& state_num {states[all_board_symbols()]};
    //cout << state_num;
    log.push_back(get_string(from)+" "+get_string(to));
    return true;    
    
}

bool board::can_en_passant(const position& passing, const position& to_pass)
{
    piece* pce{board_matrix[make_index_8(passing)]};
    piece* pce_to_pass{board_matrix[make_index_8(to_pass)]};

    if (!pce_to_pass || !pce)   // non c'è una pedina in pos_to_pass
    {
        return false; // da def, forse eccezione o altro
    }

    if (pce->can_promote()) // in generale se è un pedone
    {
        //ufficiale: pce e' un pawn

        if(pce_to_pass->get_can_be_passed() && pce_to_pass->get_player() != pce->get_player())
        {
            return true;
        }
        else
        return false;        

    }
    
    return false;

    /*vector<pawn> pl_pawns = player_pawns[pce->get_player()];
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

        }
    }
    return false;*/
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


bool board::is_castling(const position& from, const position& to){
    piece* _king = board_matrix[make_index_8(from)];

    if(!(from == position(7, 4)) || !(from == position(0, 4))){
        return false;
    }
    if(is_check(_king->get_player()) && abs(from.col - to.col) != 2){
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
        position temp_pos = position(from.row,from.col+1);
        piece* prev_in_dest{board_matrix[make_index_8(temp_pos)]};
        _king->set_position(temp_pos);
        board_matrix[make_index_8(temp_pos)] = _king;
        board_matrix[make_index_8(from)] = nullptr;
        // Se dopo una propria mossa si ha una situazione di check allora la mossa non è valida.
        if (is_check(_king->get_player()))
        {
            board_matrix[make_index_8(from)] = _king;
            _king->set_position(from);
            board_matrix[make_index_8(temp_pos)] = prev_in_dest;
            return false;
        }
        board_matrix[make_index_8(from)] = _king;
        _king->set_position(from);
        board_matrix[make_index_8(temp_pos)] = prev_in_dest;
        //qui verificare che il re non vada in scacco muovendosi in ciascuna delle due caselle     
    } else {
        rook_from = position(from.row, 7);
        rook_to = position(from.row, to.col - 1);
        for(int i = 7; i > from.col; i--){
            if(!board_matrix[make_index_8(from.row,i)])
                return false;
        }
        position temp_pos = position(from.row,from.col-1);
        piece* prev_in_dest{board_matrix[make_index_8(temp_pos)]};
        _king->set_position(temp_pos);
        board_matrix[make_index_8(temp_pos)] = _king;
        board_matrix[make_index_8(from)] = nullptr;
        // Se dopo una propria mossa si ha una situazione di check allora la mossa non è valida.
        if (is_check(_king->get_player()))
        {
            board_matrix[make_index_8(from)] = _king;
            _king->set_position(from);
            board_matrix[make_index_8(temp_pos)] = prev_in_dest;
            return false;
        }
        board_matrix[make_index_8(from)] = _king;
        _king->set_position(from);
        board_matrix[make_index_8(temp_pos)] = prev_in_dest;
        //qui verificare che il re non vada in scacco muovendosi in ciascuna delle due caselle
    }
    piece* prev_in_dest{board_matrix[make_index_8(to)]};
    _king->set_position(to);
    board_matrix[make_index_8(to)] = _king;
    board_matrix[make_index_8(from)] = nullptr;
    // Se dopo una propria mossa si ha una situazione di check allora la mossa non è valida.
    if (is_check(_king->get_player()))
    {
        board_matrix[make_index_8(from)] = _king;
        _king->set_position(from);
        board_matrix[make_index_8(to)] = prev_in_dest;
        return false;
    }
    board_matrix[make_index_8(from)] = _king;
    _king->set_position(from);
    board_matrix[make_index_8(to)] = prev_in_dest;

    piece* _rook = board_matrix[make_index_8(rook_from)];
    if(!_rook->get_init_pos() && !_king->get_init_pos()){
        return false;
    }
    return true;
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

std::vector<position> board::get_player_pieces_positions(player_id player)
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

        board_matrix[make_index_8(PAWN_ROW_PLAYER_2, i)] = &player_pawns[player_id::player_2][i];
        board_matrix[make_index_8(PAWN_ROW_PLAYER_1, i)] = &player_pawns[player_id::player_1][i];
    }


    // ----------- Inserimento knights ----------- 

    player_knights[PLAYER_1].push_back(knight(position(7, 1), player_id::player_1));
    player_knights[PLAYER_2].push_back(knight(position(0, 1), player_id::player_2));
    player_knights[PLAYER_1].push_back(knight(position(7, 6), player_id::player_1));
    player_knights[PLAYER_2].push_back(knight(position(0, 6), player_id::player_2));
    

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
    
}

void board::print_board()
{
   for (int i = 0; i < board_size; i++)
    {
       std::cout << board_size - i << " ";

       cout << row_symbols(i);

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
Mi restituisce una stringa con i simboli della riga i della board (compresi gli spazi)
*/
string board::row_symbols(int i)
{
    string str_board;

    for (int j = 0; j < board_size; j++)
    {
        piece* p = board_matrix[make_index_8(i, j)];
        if (p == nullptr)
        {
           str_board += " ";
        }
        else
        {
           str_board += p->symbol();
           //std::cout << p->get_position();
           //std::cout << "*";
        } 
    }

    return str_board;
}

string board::all_board_symbols()
{
    string all_symbols;

    for(int i = 0; i < board_size; i++)
    {
        //cout << "funziona " << i << std::endl;
        all_symbols += row_symbols(i);
    }

    //cout << all_symbols << endl;
    return all_symbols;
}

/*
Ci dice se una certa "posizione" della board (rappresentata dalla stringa str) e' capitata 3 volte nella stessa partita. Se cio' si verifica, la partita termina per patta (facciamo obbligatoriamente?!?!?!)
*/
/*bool board::too_much_reps(string str)  
{
    if(states[str] && states[str] == 3)
        return true;

    return false;
}*/


/*
La funzione is_draw ci permette di sapere se, prima della prossima mossa, si e' in una condizione in cui e' possibile procedere con la patta, ovvero interrompere la partita (in parita') per scelta o per evitare di continuare a giocare all'infinito
*/
bool board::is_draw(player_id pl)
{
    //cout << "Numero di mosse: " << get_no_pwn_no_eat() << "\n";

    //--------------- mancanza di movimenti del pedone e di catture ---------------
    constexpr int limit {50};
    constexpr int reps_limit {3};
    if(get_no_pwn_no_eat() == limit /*|| too_much_reps(all_board_symbols())*/)
    {
        cout << "limite superato\n";
        return true;
    }

    //--------------- patta per mancanza di mosse possibili del player pl ---------------
    piece* p;
    vector<position> possible_pos;

    for(int i = 0; i < board_size*board_size; i++)
    {
        p = board_matrix[i];

        if(p)
        {
            possible_pos = p->get_possible_positions();
        }
 
        if(p && p->get_player() == pl && p->can_move_to(possible_pos[i], board_matrix) && !is_check(pl))
        {
            return false;
        }   
    }

    return false;
}