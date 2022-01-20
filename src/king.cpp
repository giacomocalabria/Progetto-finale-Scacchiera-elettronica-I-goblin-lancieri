//Author: NICOLA MARITAN

#include "king.h"

#include <algorithm>

#include "board.h"

using namespace std;

bool king::can_move_to(const position& dest, const vector<piece*>& board_pieces)
{
    // Controllo se la posizione dest e' raggiungibile dalla pedina
    vector<position> possible_pos = get_possible_positions();
    auto it = find(possible_pos.begin(), possible_pos.end(), dest);
    if (it == possible_pos.end())
    {
        return false;
    }
    
    piece* dest_pce{board_pieces.at(make_index_8(dest))};

    /*
        Se e' presente un pezzo nella posizione di destinazione
        e se questo ha id giocatore uguale a quella di questo pezzo,
        allora non puo' muoversi sopra in quanto pedina propria.
        Se dest_pce e' false per corto circuito non verra' chiamata
        la funzione membro non causando alcun accesso a nullptr.
    */
    if (dest_pce && dest_pce->get_player() == get_player())
    {
        return false;
    }

    return true;
}

bool king::can_capture(const position& dest, const vector<piece*>& board_pieces)
{
    return this->can_move_to(dest, board_pieces);
}

inline char king::symbol(){
    return player == player_id::player_1 ? 'r' : 'R';
}

vector<position> king::get_possible_positions()
{
    vector<position> possible_pos;
    
    position possibility;
    possibility.row = pos.row;
    possibility.col = pos.col;

    // Ottengo tutte le posizioni valide di movimento
    // Riga e colonna partono da -1 incluso a 1 incluso (2 escluso)
    constexpr int min_offset{-1};
    constexpr int max_offset{2};
    for(int i = min_offset; i < max_offset; i++)
    {
        for(int j = min_offset; j < max_offset; j++)
        {
            // Se almeno uno degli offset e' diversi da 0
            if( i != 0 || j != 0)
            {
                possibility.row += i;
                possibility.col += j;

                // e se tale posizione e' valida all'interno della board
                if(is_valid_position_8(possibility))
                    possible_pos.push_back(possibility);

                possibility.row = pos.row;
                possibility.col = pos.col;
            }  
        }
    }

    // Movimenti dell'arrocco aggiuntivi: se e solo se e' nella posizione iniziale
    if (is_init_pos)
    {
        possible_pos.push_back(pos + position(0, 2));
        possible_pos.push_back(pos - position(0, 2));
    }

    return possible_pos;
}

bool king::is_check(const vector<piece*>& board_pieces)
{
    // Per ogni pezzo della board
    for(int i = 0; i < board::board_size * board::board_size; i++)
    {
        // Se il pezzo non e' nullptr e se il suo id e' diverso da quello del re
        // controllo se puo' mangiare.
        if(board_pieces.at(i) && board_pieces.at(i)->get_player() != get_player())
        {
            if(board_pieces.at(i)->can_capture(get_position(), board_pieces))
            {
                // Questo pezzo puo' mangiare il re: scacco
                return true;
            }
        }
    }
    // Allora nessun pezzo puo' mangiare il re.
    return false;
}