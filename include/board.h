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
    -------------------------------------------------------------------------
    La classe board contiene concretamente i pezzi e interfaccia i player con
    essi. Fornisce controlli sul flusso della partita, la sua visualizzazione,
    sullo scacco (attraverso i king) e sullo scacco matto.
    --------------------------------------------------------------------------
*/

class board
{
    public:
        // ------------------ Costruttore e inizializzatori ------------------
        // Default constructor
        board();

        // Copy constructor
        board(const board& other);

        /*
            Prova a muovere un pezzo della board dalla posizione from
            alla posizione to. Restituisce true se e solo se il movimento
            e' andato a buon fine.
        */
        bool move_piece(const position& from, const position& to);




        // ------------------ Funzioni membro pubbliche ------------------
        // Copy assignment
        board operator=(const board& other);

        // Ritorna stringa contenente il nome del log
        inline std::vector<std::string> get_log() const { return log; }

        // Ottiene tutti i simboli della riga i-esima
        std::string row_symbols(int i) const;

        // Ottiene tutti i simboli della board
        std::string all_board_symbols() const;

        // Print della board sullo std output
        void print_board() const;

        // Print della board su file
        void file_print_board(std::ofstream& _out_file);

        // Ottiene il puntatore ad un pezzo nella board
        piece* get_board_piece(const position& pos) const {return board_matrix.at(make_index_8(pos));}

        // Ottiene tutte le posizioni dei pezzi di un giocatore
        std::vector<position> get_player_pieces_positions(player_id player) const;

        // Ottiene tutte le posizioni dei pezzi di un giocatore ancora nella board
        std::vector<position> get_player_in_board_pieces_positions(player_id player) const;

        // Lato della board        
        static const int board_size {8};

        // ------------------ Funzioni membro di stato ------------------
        /*
            Controlla se un determinato giocatore si trova nella condizione
            di scacco.
        */
        bool is_check(player_id player_number);

        /*
            Controlla se un determinato giocatore si trova nella condizione
            di scacco matto.
        */
        bool is_checkmate(player_id player_number);

        /*
            Restituisce true se il giocatore si trova nella condizione di patta.
        */
        bool is_draw(player_id pl);

        /*
            Controlla il re di un giocatore e' ancora presente all'interno
            della board. Il controllo avviene in board_matrix, in quanto
            un pezzo non viene mai rimosso concretamente dai vector.
        */
        bool has_king_been_captured(player_id id) const;

        // Puo' eseguire arrocco?
        bool is_castling(const position& from, const position& to) const;

        // Puo' eseguire en_passant?
        bool can_en_passant(const position& passing, const position& to_pass) const;

        int get_count_draw() const {return count_draw;}
        int get_no_pwn_no_eat() const {return no_pwn_no_eat;}

        // ------------------ Funzioni membro di inserimento ------------------
        /*
            Tali funzioni si occupano di inserire un nuovo pezzo nel rispettivo
            vector e di far puntare la corretta cella della board a tale pezzo.
            L'inserimento prevede dunque di conoscere posizione di inserimento
            e id del giocatore.
        */
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
        /*
            Tale plain enumeration e' utilizzata per dedicare il dovuto
            spazio ai vector contenenti i pezzi.
        */
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
            Board concreata di puntatori a piece. L'accesso alla cella di di riga i e
            colonna j avviene tramite la formula 8*i + j.
            A tal proposito vi e' l'uso massiccio della funzione make_index_8 definita
            in position.h che si occupa di questo calcolo.
        */
        std::vector<piece*> board_matrix;
        
        /* 
            Array di dimensione 2, contenenti i vector dei pezzi dei giocatori 1 e 2. In
            questo modo per accedere ai pezzi del giocatore X basta la notazione player_piece[PLAYER_X].
            
            Essi sono di fatto dei contenitore statici dei pezzi della board: la loro
            capacità non cambia durante l'esecuzione del programma, poiché in init_board
            per ognuno di questi vector vi è un reserve della memoria necessaria. La staticità
            dei vector è indispensabile in quanto una riallocazione della memoria nel freestore
            di un vector rende in generale invalidi i riferimenti nella board. In questo modo
            si evita ogni tipo di memory leak in quanto l'allocazione dinamica della memoria è
            gestita dai vector stessi della STL, e si dispone di un modo molto comodo per avere
            a disposizione i vari pezzi. In questo modo per accedere ai pezzi del giocatore 2 basta
            la notazione player_pieces[1].

            Si noti che NON e' possibile inserire un pezzo dall'esterno, cioe' non e' possibile
            che un puntatore di board_matrix punti ad un pezzo che non si trovi all'interno di
            questi vector. Ogni board conosce le proprie pedine e ne ha comando. Non avrebbe
            senso acquisire dall'esterno qualcosa che non e' suo (e che potrebbe venir deallocato
            da un momento all'altro, causando terribili errori.)
        */
        std::vector<pawn> player_pawns[player_id::player_count];
        std::vector<knight> player_knights[player_id::player_count];
        std::vector<rook> player_rooks[player_id::player_count];
        std::vector<bishop> player_bishops[player_id::player_count];
        std::vector<king> player_king[player_id::player_count];
        std::vector<queen> player_queen[player_id::player_count];
    
        // ------------------ Funzioni membro private ------------------
    private:
        // Inizializza il gioco
        void init_game();
        
        // Inizializza la board
        void init_board();

        // Svuota la board ripulendo i pointer di board_matrix
        void to_empty();

        /*
            Inizializza la board con la configurazione di default di una partita
            di scacchi, inserendoli nella board.
        */ 
        void init_player_pieces();

        /*
            Promuove un pedone, in una certa posizione, arrivato "dalla parte opposta"
            della scacchiera. Il regolamento degli scacchi prevede che un pedone
            possa essere promosso a qualunque altro pezzo (al di fuori del re ovviamente).
            Ma nella quasi totalita' dei casi viene promosso alla regina, il pezzo
            indubbiamente piu' forte del gioco. La board di default fa cio' per evitare
            complicazioni del codice. Chiaramente ne consegue un inserimento della queen
            nei vector contenenti i pezzi, per tale motivo e' gia' allocato lo spazio
            per eventuali inserimenti (vedasi init_player_pieces)
        */
        bool promote(const position& pos);

        // Puo' eseguire mosse legali?
        bool can_do_legal_move(player_id pl) const;

    private:
        int count_draw = 0;         // tiene conto del numero di mosse fatte da tutti e 2 i giocatori
        int no_pwn_no_eat = 0;      // tiene conto del numero di mosse senza mangiate e senza movimenti di pawn
        
        /*
            Mappa con coppie stringhe interi dove una stringa definisce univocamente
            una configurazione della board. Se una configurazione si e' verificata per
            tre volte la partita termina. L'intero (valore associato alla chiave)
            e' il numero di apparizioni durante la partita. Le prestazioni sono
            logaritmiche in funzione del numero di configurazioni
            per ogni inserimento ed ispezione, garantite dalla stl
            (implementazione tramite red black trees)
        */
        std::map<std::string, int> states;
        std::vector<std::string> log; // Vector per memorizzare tutte le mosse effettuate dai giocatori
};

#endif // BOARD_H