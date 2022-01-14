//Author: EDDIE CARRARO

#include "king.h"

#include <algorithm>

#include "board.h"

using namespace std;

bool king::can_move_to(const position& dest, const vector<piece*>& board_pieces)
{
    vector<position> possible_pos = get_possible_positions();
    auto it = find(possible_pos.begin(), possible_pos.end(), dest);
    if (it == possible_pos.end())
    {
        return false;
    }
    
    piece* dest_pce{board_pieces.at(make_index_8(dest))};
    /*
        Se è presente un pezzo nella posizione di destinazione
        e se questo ha id giocatore uguale a quella di questo pezzo,
        allora non può muoversi sopra in quanto pedina propria.
        Se dest_pce è false per corto circuito non verrà chiamata
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

    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            if( i != 0 || j != 0)
            {
                possibility.row += i;
                possibility.col += j;

                if(possibility.col > -1 && possibility.col < 8 && possibility.row > -1 && possibility.row < 8) //cambiare sta roba !!
                {
                    possible_pos.push_back(possibility);
                }

                possibility.row = pos.row;
                possibility.col = pos.col;
            }  
        }
    }
    return possible_pos;
}

bool king::is_check(const std::vector<piece*>& board_pieces)
{
    //cout << "CALL IS_CHECK\n";
    for(int i = 0; i < board::board_size * board::board_size; i++)
    {
        if(board_pieces[i] && board_pieces[i]->get_player() != get_player()) //NOTA: ricordati la condizione (board[i])!
        { 
            // Commenti UTILISSIMI per debug: non eliminare pls
            //cout << board_pieces[i]->symbol() << ", " << board_pieces[i]->get_position();
            if((*(board_pieces[i])).can_capture(get_position(), board_pieces))
            {
                //cout << "CHEKS\n";
                return true;
            }
            //cout << "NOT CHECKS\n";
        }
    }
    return false;
}