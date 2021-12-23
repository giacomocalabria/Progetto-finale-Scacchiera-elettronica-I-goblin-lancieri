//Author:

#include "king.h"
#include "board.h"
#include <algorithm>

using namespace std;

bool king::can_move_to(const position& dest, piece* const mat[][8]){
    vector<position> possible_pos = get_possible_positions();
    //vector<position>::iterator it;
    auto it = find(possible_pos.begin(), possible_pos.end(), dest);
    if (it == possible_pos.end()) 
        return false;
    //...
}

inline char king::symbol(){
    return player == board::PLAYER_1 ? 'r' : 'R';
}

vector<position> king::get_possible_positions(){
    vector<position> possible_pos;
    
    position dest = pos + position(0, 1);
    if(dest.col > 0 && dest.col < 7 && dest.row > 0 && dest.row < 7)
        possible_pos.push_back(dest);

    dest = pos + position(1, 1);
    if(dest.col > 0 && dest.col < 7 && dest.row > 0 && dest.row < 7)
        possible_pos.push_back(dest);

    dest = pos + position(1, 0);
    if(dest.col > 0 && dest.col < 7 && dest.row > 0 && dest.row < 7)
        possible_pos.push_back(dest);
    
    dest = pos + position(1, -1);
    if(dest.col > 0 && dest.col < 7 && dest.row > 0 && dest.row < 7)
        possible_pos.push_back(dest);
    
    dest = pos + position(0, -1);
    if(dest.col > 0 && dest.col < 7 && dest.row > 0 && dest.row < 7)
        possible_pos.push_back(dest);
    
    dest = pos + position(-1, -1);
    if(dest.col > 0 && dest.col < 7 && dest.row > 0 && dest.row < 7)
        possible_pos.push_back(dest);
    
    dest = pos + position(-1, 0);
    if(dest.col > 0 && dest.col < 7 && dest.row > 0 && dest.row < 7)
        possible_pos.push_back(dest);
    
    dest = pos + position(-1, 1);
    if(dest.col > 0 && dest.col < 7 && dest.row > 0 && dest.row < 7)
        possible_pos.push_back(dest);

    return possible_pos;
}