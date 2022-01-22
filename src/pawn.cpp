// Author: GIACOMO CALABRIA

#include "pawn.h"

#include <algorithm>

#include "board.h"

using namespace std;

/*  ------------------------------------------------------------------
    Costruttore della classe pawn. Essa semplicemente richiama il
    costruttore della base class piece. Ciò avviene in modo totalmente
    analogo nelle altre classi derivate da piece.
    ------------------------------------------------------------------
*/
pawn::pawn(const position& _pos, player_id _player) : piece(_pos, _player) {}

bool pawn::can_move_to(const position& dest, const vector<piece*>& board_pieces)
{
    if (!is_valid_position_8(dest))
        return false;

    //------- controllo se la posizione dest e' raggiungibile dalla pedina -------
    vector<position> possible_positions = get_possible_positions();
    auto it = find(possible_positions.begin(), possible_positions.end(), dest);
    // Se la destinazione non è all' interno delle possibili posizioni
    // la funzione can_move_to ritorna falso
    if (it == possible_positions.end())
        return false;

    int sign = player == player_id::player_1 ? -1 : 1;  // orientazione
    if (dest == pos + (sign * position(1, 0)))
    {
        // Allora si sta muovendo in avanti
        if (board_pieces.at(make_index_8(dest)))
        {
            return false;
        }
        is_init_pos = false;
        can_be_passed = false;
        return true;
    }

    if (dest == pos + (sign * position(2, 0)))
    {
        // Allora si sta muovendo in avanti di 2 posizioni
        if (board_pieces.at(make_index_8(dest)) || board_pieces.at(make_index_8(dest.row - sign, dest.col)))
        {
            //Se ci sono pedine nella traiettoria di movimento, non posso fare la mossa e ritorna quindi false...
            return false;
        }
        /*...altrimenti la mossa e' lecita: pongo is_init_pos a false (non si
        trovera' sicuramente piu' nella sua posizione iniziale)*/
        is_init_pos = false;
        //il pedone in questione, solo nella prossima mossa dell'avversario, puo' essere catturato "in passant"
        can_be_passed = true;
        
        return true;
    }

    // Sicuramente si sta muovendo in diagonale (gli altri casi hanno già portato a conclusione)
    piece* other = board_pieces.at(make_index_8(dest));
    if (other)
    {
        if (player != other->get_player())
        {
            is_init_pos = false;
            can_be_passed = false;
            return true;
        }
    }

    //Se siamo arrivati fin qui, significa che la mossa non e' sicuramente lecita
    return false;
}

//Serve per definire la condizione di scacco del re avversario
bool pawn::can_capture(const position& dest, const vector<piece*>& board_pieces)
{
    piece* other = board_pieces.at(make_index_8(dest));

    // Ovviamente se nella cella di destinazione non c'è nulla non può mangiare.
    if (!other)
    {
        return false;
    }

    int sign = player == player_id::player_1 ? -1 : 1;  // orientazione

    if(other && (dest == pos + (sign * position(1, 1)) || dest == pos + (sign * position(1, -1))))
    {
        /*Se tale pedina però è dello stesso giocatore
        di questo pedone significa che non potrà mangiarlo*/
        if (other->get_player() == get_player())
            return false;

        is_init_pos = false;
        can_be_passed = false;
        return true;
    }

    return false;
}

inline char pawn::symbol()
{
    return player == player_id::player_1 ? 'p' : 'P';
}

/*  
    Il pawn ha come possibili posizioni principali le sue tre
    celle frontali. Se si trova nella posizione iniziale allora
    ha la possibilità di fare un salto in avanti di 2.
*/
vector<position> pawn::get_possible_positions()
{
    vector<position> possible_positions;
    int sign = player == player_id::player_1 ? -1 : 1;  // orientazione
    position dest;
    
    // Se si trova nella posizione iniziale
    if (is_init_pos)
    {
        dest = pos + (sign * position(2, 0));
        if(is_valid_position_8(dest))
            possible_positions.push_back(dest);
    }

    dest = pos + (sign * position(1, 0));
    if(is_valid_position_8(dest))
        possible_positions.push_back(dest);
    
    dest = pos + (sign * position(1, 1));
    if(is_valid_position_8(dest))
        possible_positions.push_back(dest);
    
    dest = pos + (sign * position(1, -1));
    if(is_valid_position_8(dest))
        possible_positions.push_back(dest);

    /*
        Il movimento dell'en passant è già incluso nel movimento
        in diagonale. move_piece della board si occuperà poi
        di fare i controlli del caso.
    */

    return possible_positions;
}
