#include "rook.h"
#include "board.h"
#include <algorithm>

using namespace std;

void rook::move(const position& to){
    
}

bool rook::can_move_to(const position& dest, piece* const mat[][8]){
    
}

inline char rook::symbol(){
    return player == board::PLAYER_1 ? 't' : 'T';
}

vector<position> rook::get_possible_positions(){
    vector<position> possible_pos;

    return possible_pos;
}