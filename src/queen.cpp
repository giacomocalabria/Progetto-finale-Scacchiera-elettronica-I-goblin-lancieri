//Author: 

#include "queen.h"
#include "board.h"
#include <algorithm>

using namespace std;

void queen::move(const position& to){
    
}

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
    //...
}