// Author: GIACOMO CALABRIA

#include "knight.h"
#include "board.h"
#include <algorithm>

using namespace std;

bool knight::can_move_to(const position& dest, piece* const mat[][8]){
    vector<position> possible_pos = get_possible_positions();
    //vector<position>::iterator it;
    auto it = find(possible_pos.begin(), possible_pos.end(), dest);
    if (it == possible_pos.end()) 
        return false;
    
    piece* other = mat[dest.row][dest.col];
    if (other){
        if(player != other -> get_player()){
            return true;
        }
        else return false;
    }
    return true;
}

inline char knight::symbol(){
    return player == board::PLAYER_1 ? 'c' : 'C';
}

vector<position> knight::get_possible_positions(){
    vector<position> possible_pos;

    position dest = pos + position(1, 2);
    if(dest.col > 0 && dest.col < 7 && dest.row > 0 && dest.row < 7)
        possible_pos.push_back(dest);

    dest = pos + position(2, 1);
    if(dest.col > 0 && dest.col < 7 && dest.row > 0 && dest.row < 7)
        possible_pos.push_back(dest);

    dest = pos + position(1, -2);
    if(dest.col > 0 && dest.col < 7 && dest.row > 0 && dest.row < 7)
        possible_pos.push_back(dest);
    
    dest = pos + position(2, -1);
    if(dest.col > 0 && dest.col < 7 && dest.row > 0 && dest.row < 7)
        possible_pos.push_back(dest);
    
    dest = pos + position(-1, -2);
    if(dest.col > 0 && dest.col < 7 && dest.row > 0 && dest.row < 7)
        possible_pos.push_back(dest);
    
    dest = pos + position(-2, -1);
    if(dest.col > 0 && dest.col < 7 && dest.row > 0 && dest.row < 7)
        possible_pos.push_back(dest);
    
    dest = pos + position(-1, 2);
    if(dest.col > 0 && dest.col < 7 && dest.row > 0 && dest.row < 7)
        possible_pos.push_back(dest);
    
    dest = pos + position(-2, 1);
    if(dest.col > 0 && dest.col < 7 && dest.row > 0 && dest.row < 7)
        possible_pos.push_back(dest);

    return possible_pos;
}

