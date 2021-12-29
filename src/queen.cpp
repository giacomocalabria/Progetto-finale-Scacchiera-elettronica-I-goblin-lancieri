//Author: EDDIE CARRARO

#include "queen.h"
#include "board.h"
#include <algorithm>

using namespace std;

bool queen::can_move_to(const position& dest, const vector<piece*>& board_pieces)
{
    //return false;   // temporaneoooooooooooooo per usare computer_player
    
    vector<position> possible_positions = get_possible_positions();
    auto it = find(possible_positions.begin(), possible_positions.end(), dest);
    if (it == possible_positions.end())
        return false;

    //std::cout << "Destination in possible_positions.\n";
    position cursor = pos;
    piece* other;
    
    // ----------- scansione in basso -----------  
    if (dest.row > pos.row)
    {
        //std::cout << "Scansione in basso.\n";
        cursor = cursor + position(1, 0);
        while (cursor.row < piece::max_position && cursor.row < dest.row)
        {
            other = board_pieces[make_index_8(cursor)];
            if (other)
                return false;
            cursor = cursor + position(1, 0);
        }
    }
    // ----------- scansione in alto -----------
    else if (dest.row < pos.row)
    {
        //std::cout << "Scansione in alto.\n";
        cursor = cursor - position(1, 0);
        while (cursor.row >= piece::min_position && cursor.row > dest.row)
        {
            other = board_pieces[make_index_8(cursor)];
            if (other)
            {
                //cout << "Obstacle.\n";
                return false;
            }
            cursor = cursor - position(1, 0);
        }
    }
    // ----------- scansione a destra -----------
    else if (dest.col > pos.col)
    {
        //std::cout << "Scansione a destra.\n";
        cursor = cursor + position(0, 1);
        while (cursor.col < piece::max_position && cursor.col < dest.col)
        {    
            other = board_pieces[make_index_8(cursor)];
            if (other)
                return false;
            cursor = cursor + position(0, 1);
        }
    }
    // ----------- scansione a sinistra -----------
    else if (dest.col < pos.col)
    {
        //std::cout << "Scansione a sinistra.\n";
        cursor = cursor - position(0, 1);
        while (cursor.col >= piece::min_position && cursor.col > dest.col)
        {
            other = board_pieces[make_index_8(cursor)];
            if (other)
                return false;
            cursor = cursor - position(0, 1);
        }
    }

    // se la cella di arrivo è occupata ed è occupata da un pezzo del stesso giocatore -> rest falso
    other = board_pieces[make_index_8(dest)];
    //cout << other->symbol();
    if (other && other->get_player() == player)
    {
        //cout << "Same color.\n";
        return false;
    }
    return true;


    cursor = pos;       //posizione che avanza fino a dest
    piece* go_piece = board_pieces[make_index_8(cursor)];            //pedina di ogni posizione considerata fino a dest

    if(dest.col > pos.col)          //controllo se la destinazione e' a "destra" rispetto alla current_pos
    {
        if(dest.row > pos.row)      //controllo se la destinazione e' "in alto" (a destra) rispetto alla current_pos
        {
            while(cursor.row != dest.row && cursor.col != dest.col)
            {
                cursor = position(cursor.row + 1, cursor.col + 1);
                go_piece = board_pieces[make_index_8(cursor)];

                if(go_piece != nullptr && (*go_piece).get_player() == this->get_player())
                {
                    return false;
                }
            }
        }
        else if(dest.row < pos.row)
        {
            while(cursor.row != dest.row && cursor.col != dest.col)
            {
                cursor = position(cursor.row - 1, cursor.col + 1);
                go_piece = board_pieces[make_index_8(cursor)];

                if(go_piece != nullptr && (*go_piece).get_player() == this->get_player())
                {
                    return false;
                }
            }
        }
        else
            return false;

        return true;
    }
    else if(dest.col < pos.col)          //controllo se la destinazione e' a "sinistra" rispetto alla current_pos
    {
        if(dest.row > pos.row)      //controllo se la destinazione e' "in alto" (a sinistra) rispetto alla current_pos
        {
            while(cursor.row != dest.row && cursor.col != dest.col)
            {
                cursor = position(cursor.row + 1, cursor.col - 1);
                go_piece = board_pieces[make_index_8(cursor)];

                if(go_piece != nullptr && (*go_piece).get_player() == this->get_player())
                {
                    return false;
                }
            }
        }
        else if(dest.row < pos.row)
        {
            while(cursor.row != dest.row && cursor.col != dest.col)
            {
                cursor = position(cursor.row - 1, cursor.col - 1);
                go_piece = board_pieces[make_index_8(cursor)];

                if(go_piece != nullptr && (*go_piece).get_player() == this->get_player())
                {
                    return false;
                }
            }
        }
        else
            return false;
    }
    else
        return false;


    return true;
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
    return possible_pos;    // temporaneo

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