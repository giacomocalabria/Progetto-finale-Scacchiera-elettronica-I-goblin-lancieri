// Author: NICOLA MARITAN

#include "rook.h"

#include <algorithm>

#include "board.h"

using namespace std;


bool rook::can_move_to(const position& dest, const vector<piece*>& board_pieces)
{
    if (!is_valid_position_8(dest))
    {
        return false;
    }

    vector<position> possible_positions = get_possible_positions();
    //std::cout << "Positions generated (Rook).\n";
    
    /*
        Ricerca della posizione di destinazione all'interno
        delle posizioni possibili. Chiaramente se non è
        presente allora non si può muovere su quella posizione
        a prescindere.
    */
    vector<position>::iterator it;
    it = find(possible_positions.begin(), possible_positions.end(), dest);
    if (it == possible_positions.end())
        return false;

    //std::cout << "Destination in possible_positions.\n";
    position cursor = pos;
    piece* other;
    
    /*
        La scansione avviene solamente lungo una direzione: dipende
        da dove si trova dest rispetto a pos. Ad esempio, se la riga
        di dest è maggiore di pos, allora la scansione avviene solo
        verso il basso.
    */

    // ----------- scansione in basso -----------  
    if (dest.row > pos.row)
    {
        //std::cout << "Scansione in basso.\n";
        cursor = cursor + position(1, 0);
        while (is_valid_position_8(cursor) && cursor.row < dest.row)
        {
            other = board_pieces[make_index_8(cursor)];
            /*
                other restituisce true se la pedina
                "andrebbe a sbattere" prima di raggiungere
                la posizione di destinazione. Ragionamento
                analogo per le 4 diagonali.
            */
            if (other)
                return false;
            cursor = cursor + position(1, 0);
        }
    }
    // ----------- scansione in alto -----------
    else if (dest.row < pos.row)
    {
        //std::cout << "Scansione in alto.\n";
        cursor = cursor - position(1, 0);
        while (is_valid_position_8(cursor) && cursor.row > dest.row)
        {
            other = board_pieces[make_index_8(cursor)];
            if (other)
            {
                //cout << "Obstacle.\n";
                return false;
            }
            cursor = cursor - position(1, 0);
        }
    }
    // ----------- scansione a destra -----------
    else if (dest.col > pos.col)
    {
        //std::cout << "Scansione a destra.\n";
        cursor = cursor + position(0, 1);
        while (is_valid_position_8(cursor) && cursor.col < dest.col)
        {    
            other = board_pieces[make_index_8(cursor)];
            if (other)
                return false;
            cursor = cursor + position(0, 1);
        }
    }
    // ----------- scansione a sinistra -----------
    else if (dest.col < pos.col)
    {
        //std::cout << "Scansione a sinistra.\n";
        cursor = cursor - position(0, 1);
        while (is_valid_position_8(cursor) && cursor.col > dest.col)
        {
            other = board_pieces[make_index_8(cursor)];
            if (other)
                return false;
            cursor = cursor - position(0, 1);
        }
    }

    // se la cella di arrivo è occupata ed è occupata da un pezzo del stesso giocatore -> rest falso
    other = board_pieces[make_index_8(dest)];
    //cout << other->symbol();
    if (other && other->get_player() == player)
    {
        //cout << "Same color.\n";
        return false;
    }
    return true;
}

bool rook::can_capture(const position& dest, const vector<piece*>& board_pieces)
{
    return this->can_move_to(dest, board_pieces);
}

inline char rook::symbol()
{
    return player == player_id::player_1 ? 't' : 'T';
}

std::vector<position> rook::get_possible_positions()
{
    std::vector<position> possible_positions;

    position cursor = pos;

    
    // ----------- scansione a destra -----------
    //std::cout << "Scansione a destra.\n";
    cursor = pos;
    while (cursor.col < piece::max_position)
    {
        cursor = cursor + position(0, 1);
        possible_positions.push_back(cursor);
    }

    // ----------- scansione a sinistra -----------
    //std::cout << "Scansione a sinistra.\n";
    cursor = pos;
    while (cursor.col > piece::min_position)
    {
        cursor = cursor - position(0, 1);
        possible_positions.push_back(cursor);
    }

    // ----------- scansione in basso -----------
    //std::cout << "Scansione in basso.\n";
    cursor = pos;
    while (cursor.row < piece::max_position)
    {
        cursor = cursor + position(1, 0);
        possible_positions.push_back(cursor);
    }

    // ----------- scansione in alto -----------
    //std::cout << "Scansione in alto.\n";
    cursor = pos;
    while (cursor.row > piece::min_position)
    {
        cursor = cursor - position(1, 0);
        possible_positions.push_back(cursor);
    }
    

    /*
    // ----------- scansione a destra -----------
    //std::cout << "Scansione a destra.\n";
    cursor = pos + position(0, 1);
    while (is_valid_position_8(cursor))
    { 
        possible_positions.push_back(cursor);
        cursor = cursor + position(0, 1);
    }

    // ----------- scansione a sinistra -----------
    //std::cout << "Scansione a sinistra.\n";
    cursor = pos - position(0, 1);
    while (is_valid_position_8(cursor))
    {
        possible_positions.push_back(cursor);
        cursor = cursor - position(0, 1);
    }

    // ----------- scansione in basso -----------
    //std::cout << "Scansione in basso.\n";
    cursor = pos + position(1, 0);
    while (is_valid_position_8(pos))
    {
        possible_positions.push_back(cursor);
        cursor = cursor + position(1, 0);
    }

    // ----------- scansione in alto -----------
    //std::cout << "Scansione in alto.\n";
    cursor = pos - position(1, 0);
    while (cursor.row > piece::min_position)
    {
        possible_positions.push_back(cursor);
        cursor = cursor - position(1, 0);
    }
    */


    /*
        Ora possible_positions contiene tutte le posizioni
        possibili (anche non raggiungibili effettivamente)
        che sono quelle lungo la stessa riga e colonna di pos.
    */

    return possible_positions;
}

