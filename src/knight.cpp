// Author: GIACOMO CALABRIA

#include "knight.h"

#include <algorithm>

using namespace std;

bool knight::can_move_to(const position& dest, const vector<piece*>& board_pieces){

    //------- controllo se la posizione dest e' raggiungibile dalla pedina -------
    vector<position> possible_pos = get_possible_positions();
    auto it = find(possible_pos.begin(), possible_pos.end(), dest);
    // Se la destinazione non è all' interno delle possibili posizioni
    // la funzione can_move_to ritorna falso
    if (it == possible_pos.end()) 
        return false;
    
    piece* other = board_pieces.at(make_index_8(dest));

    //Non è necessario controllare le posizioni su cui trasla il cavallo in quanto 
    //il cavallo può scavalcare le altre pedine siano esse avversarie o non.
    if (other){
        //Il cavallo non può andare su una pedina dello stesso colore
        if(player != other -> get_player()){
            return true;
        }
        else return false;
    }
    return true;
}

bool knight::can_capture(const position& dest, const vector<piece*>& board_pieces){
    //Il cavallo può sempre catturare un pezzo avversario nella casa di destinazione
    return this->can_move_to(dest, board_pieces);
}

inline char knight::symbol(){
    return player == player_id::player_1 ? 'c' : 'C';
}

/*
    La mossa del cavallo è una mossa a "L".
    Prima di inserire una posizione nel vector controllo che tale posizione sia
    all' interno dei range della scacchiera.
*/

/*vector<position> knight::get_possible_positions(){ 
    vector<position> possible_pos;
    position dest;

    for(int i = -1; i < 2; i + 2){
        for(int j = -1; j < 2; j + 2){
            dest = pos + position(1 * j, 2 * i);
            if(is_valid_position_8(dest))
                possible_pos.push_back(dest);

            dest = pos + position(2 * j, 1 * i);
            if(is_valid_position_8(dest))
                possible_pos.push_back(dest);
        }
    }

    return possible_pos;
}*/

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
