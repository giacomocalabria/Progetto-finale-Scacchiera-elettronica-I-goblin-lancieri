// Author: GIACOMO CALABRIA

#include "knight.h"

#include <algorithm>

//#include "board.h"

using namespace std;

bool knight::can_move_to(const position& dest, const vector<piece*>& board_pieces){
    //cout << "Call a can_move_to di knight; from : " << pos << ", dest: " << dest << endl;
    vector<position> possible_pos = get_possible_positions();
    auto it = find(possible_pos.begin(), possible_pos.end(), dest);
    if (it == possible_pos.end()) 
        return false;
    
    piece* other = board_pieces[make_index_8(dest)];
    if (other){
        if(player != other -> get_player()){
            return true;
        }
        else return false;
    }
    return true;
}

bool knight::can_capture(const position& dest, const vector<piece*>& board_pieces){
    return this->can_move_to(dest, board_pieces);
}

inline char knight::symbol(){
    return player == player_id::player_1 ? 'c' : 'C';
}

vector<position> knight::get_possible_positions(){ 
    vector<position> possible_pos;

    position dest = pos + position(1, 2);
    if(is_valid_position_8(dest))
        possible_pos.push_back(dest);

    dest = pos + position(2, 1);
    if(is_valid_position_8(dest))
        possible_pos.push_back(dest);

    dest = pos + position(1, -2);
    if(is_valid_position_8(dest))
        possible_pos.push_back(dest);
    
    dest = pos + position(2, -1);
    if(is_valid_position_8(dest))
        possible_pos.push_back(dest);
    
    dest = pos + position(-1, -2);
    if(is_valid_position_8(dest))
        possible_pos.push_back(dest);
    
    dest = pos + position(-2, -1);
    if(is_valid_position_8(dest))
        possible_pos.push_back(dest);
    
    dest = pos + position(-1, 2);
    if(is_valid_position_8(dest))
        possible_pos.push_back(dest);
    
    dest = pos + position(-2, 1);
    if(is_valid_position_8(dest))
        possible_pos.push_back(dest);

    return possible_pos;
}

