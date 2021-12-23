#include "bishop.h"
#include "board.h"
#include <algorithm>

using namespace std;

void bishop::move(const position& to){
    
}

bool bishop::can_move_to(const position& dest, piece* const mat[][8]){

}

inline char bishop::symbol(){
    return player == board::PLAYER_1 ? 'a' : 'A';
}

vector<position> bishop::get_possible_positions(){
    vector<position> possible_pos;

    return possible_pos;
}