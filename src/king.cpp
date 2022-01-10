//Author: EDDIE CARRARO

#include "king.h"

#include <algorithm>

#include "board.h"

using namespace std;

bool king::can_move_to(const position& dest, const vector<piece*>& board_pieces)
{
    //return false;

    vector<position> possible_pos = get_possible_positions();
    //vector<position>::iterator it;
    auto it = find(possible_pos.begin(), possible_pos.end(), dest);
    if (it == possible_pos.end())
    {
        return false;
    }
    
    //return !(is_check(board_pieces, dest));
    return true;
}

bool king::can_capture(const position& dest, const vector<piece*>& board_pieces)
{
    return this->can_move_to(dest, board_pieces);
}

inline char king::symbol(){
    return player == board::PLAYER_1 ? 'r' : 'R';
}

bool king::can_promote()
{
    return false;
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
    for(int i = 0; i < board::board_size * board::board_size; i++)
    {
        if(board_pieces[i] && board_pieces[i]->get_player() != get_player()) //NOTA: ricordati la condizione (board[i])!
        { 
            cout << board_pieces[i]->symbol() << ", " << board_pieces[i]->get_position();
            if((*(board_pieces[i])).can_capture(get_position(), board_pieces))
            {
                cout << "CHEKS\n";
                return true;
            }
            cout << "NOT CHECKS\n";
        }
    }
    return false;
}