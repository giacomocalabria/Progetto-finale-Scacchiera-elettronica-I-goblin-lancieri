//Author:

#include "king.h"
#include "board.h"
#include <algorithm>

using namespace std;

void king::move(const position& to){
    
}

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
    //...
}