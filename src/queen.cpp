//Author: EDDIE CARRARO

#include "queen.h"
#include "board.h"
#include <algorithm>

using namespace std;

bool queen::can_move_to(const position& dest, const vector<piece*>& board_pieces)
{
    vector<position> possible_pos = get_possible_positions();
    //vector<position>::iterator it;
    auto it = find(possible_pos.begin(), possible_pos.end(), dest);
    if (it == possible_pos.end()) 
        return false;
    //...

    return false;
}

bool queen::can_eat(const position& dest, const vector<piece*>& board_pieces)
{
    return this->can_move_to(dest, board_pieces);
}

inline char queen::symbol(){
    return player == board::PLAYER_1 ? 'd' : 'D';
}

vector<position> queen::get_possible_positions(){
    vector<position> possible_pos;
    position dest; //position(riga, colonna)
    
    //riga intera e colonna intera
    for(int i = 0; i < 7; i++){
        dest = position(i, pos.col);
        if(!(dest == pos))
            possible_pos.push_back(dest);
        dest = position(pos.row, i);
        if(!(dest == pos))
            possible_pos.push_back(dest);
    }

    
    if(pos.col >= pos.row ){
        //diagonale secondaria
        for(int i = 0; i < 7 - (pos.col - pos.row - 1); i++){ 
            dest = position(i, i + (pos.col - pos.row));
            if(!(dest == pos))
                possible_pos.push_back(dest);
        }
    }
    else{
        //diagonale secondaria
        for(int i = 0; i < 7 - (pos.row - pos.col - 1); i++){ 
            dest = position(i + (pos.row - pos.col), i);
            if(!(dest == pos))
                possible_pos.push_back(dest);
        }
    }
    if(pos.row + pos.col < 7){
        //diagonale primaria
        for(int i = 0; i < (pos.row + pos.col); i++){
        dest = position((pos.col + pos.row) - i, i);
        if(!(dest == pos))
            possible_pos.push_back(dest);
        }
    }
    else{
        //diagonale secondaria
        for(int i = (pos.row + pos.col) - 7; i < 7; i++){
        dest = position(7 + pos.row - i , i);
        if(!(dest == pos))
            possible_pos.push_back(dest);
        }
    }

    return possible_pos;
}