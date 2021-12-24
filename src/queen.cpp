//Author: 

#include "queen.h"
#include "board.h"
#include <algorithm>

using namespace std;

bool queen::can_move_to(const position& dest, piece* const mat[][8]){
    vector<position> possible_pos = get_possible_positions();
    //vector<position>::iterator it;
    auto it = find(possible_pos.begin(), possible_pos.end(), dest);
    if (it == possible_pos.end()) 
        return false;
    //...
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

    //diagonale principale
    if(pos.col-pos.row > 0){
        for(int i = 0; i < 7 - (pos.col - pos.row - 1); i++){ 
            dest = position((pos.col-pos.row) + i, i);
            if(!(dest == pos))
                possible_pos.push_back(dest);
        }
    }
    else{
        for(int i = 0; i < 7 - (pos.row - pos.col - 1); i++){ 
            dest = position((pos.row - pos.col) + i, i);
            if(!(dest == pos))
                possible_pos.push_back(dest);
        }
    }

    //diagonale secondaria
    for(int i = 0; i < 7 - (pos.row-pos.col); i++){
        dest = position(7+(pos.col-pos.row), i);
        if(!(dest == pos))
            possible_pos.push_back(dest);
    }
}