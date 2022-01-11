//Author: EDDIE CARRARO

#include "queen.h"

#include <algorithm>

#include "board.h"

using namespace std;

bool queen::can_move_to(const position& dest, const vector<piece*>& board_pieces)
{
    vector<position> possible_pos = get_possible_positions();
    auto it = find(possible_pos.begin(), possible_pos.end(), dest);
    if (it == possible_pos.end()) 
        return false;

    position cursor = pos;
    piece* other;
    
    /*
        La scansione avviene solamente lungo una direzione: dipende
        da dove si trova dest rispetto a pos. Ad esempio, se la riga
        di dest è maggiore di pos, allora la scansione avviene solo
        verso il basso.
    */

    // ----------- scansione in basso -----------  
    if (dest.row > pos.row)
    {
        //std::cout << "Scansione in basso.\n";
        cursor = cursor + position(1, 0);
        while (cursor.row < piece::max_position && cursor.row < dest.row)
        {
            other = board_pieces[make_index_8(cursor)];
            /*
                other restituisce true se la pedina
                "andrebbe a sbattere" prima di raggiungere
                la posizione di destinazione. Ragionamento
                analogo per le 4 diagonali.
            */
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

    cursor = pos;        //posizione che avanza fino a dest
    other = board_pieces[make_index_8(cursor)];            //pedina di ogni posizione considerata fino a dest

    if(dest.col > pos.col)          //controllo se la destinazione e' a "destra" rispetto alla pos corrente
    {
        // ----------- scansione in basso a destra -----------
        if(dest.row > pos.row)
        {
            while(cursor.row != dest.row && cursor.col != dest.col)
            {
                cursor = position(cursor.row + 1, cursor.col + 1);
                other = board_pieces[make_index_8(cursor)];

                if(other != nullptr && (*other).get_player() == this->get_player())
                {
                    return false;
                }
            }
        }
        // ----------- scansione in alto a destra -----------
        else if(dest.row < pos.row)
        {
            while(cursor.row != dest.row && cursor.col != dest.col)
            {
                cursor = position(cursor.row - 1, cursor.col + 1);
                other = board_pieces[make_index_8(cursor)];

                if(other != nullptr && (*other).get_player() == this->get_player())
                {
                    return false;
                }
            }
        }
        else
            return false;
    }
    else if(dest.col < pos.col)          //controllo se la destinazione e' a "sinistra" rispetto alla pos corrente
    {
        // ----------- scansione in basso a sinistra -----------
        if(dest.row > pos.row)
        {
            while(cursor.row != dest.row && cursor.col != dest.col)
            {
                cursor = position(cursor.row + 1, cursor.col - 1);
                other = board_pieces[make_index_8(cursor)];

                if(other != nullptr && (*other).get_player() == this->get_player())
                {
                    return false;
                }
            }
        }
        // ----------- scansione in alto a sinistra -----------
        else if(dest.row < pos.row)
        {
            while(cursor.row != dest.row && cursor.col != dest.col)
            {
                cursor = position(cursor.row - 1, cursor.col - 1);
                other = board_pieces[make_index_8(cursor)];

                if(other != nullptr && (*other).get_player() == this->get_player())
                {
                    return false;
                }
            }
        }
        else
            return false;
    }

    return true;
}

bool queen::can_promote(){return false;}

bool queen::can_capture(const position& dest, const vector<piece*>& board_pieces)
{
    return this->can_move_to(dest, board_pieces);
}

inline char queen::symbol(){
    return player == player_id::player_1 ? 'd' : 'D';
}

vector<position> queen::get_possible_positions(){
    vector<position> possible_pos;

    position dest; //position(riga, colonna)
    
    //riga intera e colonna intera
    //for(int i = 0; i < 7; i++){     // modificato da 7 a 8: perché può andare anche nella riga/colonna di indice 7
    
    /*
        
    */

    //---------- posizioni in linea orizzontale e verticale rispetto alla regina ----------
    for (int i = min_position; i < max_position; i++)
    {
        dest = position(i, pos.col);
        if(!(dest == pos))
            possible_pos.push_back(dest);
        dest = position(pos.row, i);
        if(!(dest == pos))
            possible_pos.push_back(dest);
    }

    dest = position(pos.row + 1, pos.col + 1);
    while(dest.row < 8 && dest.row > 0 && dest.col < 8 && dest.col > 0) //boundary rispettato?
    {
        possible_pos.push_back(dest);

        dest.row++;
        dest.col++;        //controllo le posizioni successive (in cui bishop puo'andare)
    }

    dest = position(pos.row - 1, pos.col + 1);
    while(dest.row < 8 && dest.row > -1 && dest.col < 8 && dest.col > -1)   //boundary rispettato?
    {
        possible_pos.push_back(dest);

        dest.row--;
        dest.col++;        //controllo le posizioni successive (in cui bishop puo'andare)
    }

    dest = position(pos.row + 1, pos.col - 1);
    while(dest.row < 8 && dest.row > 0 && dest.col < 8 && dest.col > 0) //boundary rispettato?
    {
        possible_pos.push_back(dest);

        dest.row++;
        dest.col--;        //controllo le posizioni successive (in cui bishop puo'andare)
    }

    dest = position(pos.row - 1, pos.col - 1);
    while(dest.row < 8 && dest.row > 0 && dest.col < 8 && dest.col > 0) //boundary rispettato?
    {
        possible_pos.push_back(dest);

        dest.row--;
        dest.col--;        //controllo le posizioni successive (in cui bishop puo'andare)
    }

    return possible_pos;
}