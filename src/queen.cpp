//Author: EDDIE CARRARO

#include "queen.h"

#include <algorithm>

#include "board.h"

using namespace std;

bool queen::can_move_to(const position& dest, const vector<piece*>& board_pieces)
{
    if(!is_valid_position_8(dest))
        return false;

    //------- controllo se la posizione dest e' raggiungibile dalla pedina -------
    vector<position> possible_pos = get_possible_positions();
    auto it = find(possible_pos.begin(), possible_pos.end(), dest);
    if (it == possible_pos.end()) 
        return false;

    position cursor = pos;
    piece* other;
    
    /*  ------------------------------------------------------------
        La scansione avviene solamente lungo una direzione: dipende
        da dove si trova dest rispetto a pos. Ad esempio, se la riga
        di dest e' maggiore di pos, allora la scansione avviene solo
        verso il basso.
        ------------------------------------------------------------
    */
    // ----------- scansione in basso -----------  
    if (dest.row > pos.row)
    {
        cursor = cursor + position(1, 0);
        while (cursor.row < piece::max_position && cursor.row < dest.row)
        {
            other = board_pieces.at(make_index_8(cursor));
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
        cursor = cursor - position(1, 0);
        while (cursor.row >= piece::min_position && cursor.row > dest.row)
        {
            other = board_pieces.at(make_index_8(cursor));
            if (other)
            {
                return false;
            }
            cursor = cursor - position(1, 0);
        }
    }
    // ----------- scansione a destra -----------
    else if (dest.col > pos.col)
    {
        cursor = cursor + position(0, 1);
        while (cursor.col < piece::max_position && cursor.col < dest.col)
        {    
            other = board_pieces.at(make_index_8(cursor));
            if (other)
                return false;
            cursor = cursor + position(0, 1);
        }
    }
    // ----------- scansione a sinistra -----------
    else if (dest.col < pos.col)
    {
        cursor = cursor - position(0, 1);
        while (cursor.col >= piece::min_position && cursor.col > dest.col)
        {
            other = board_pieces.at(make_index_8(cursor));
            if (other)
                return false;
            cursor = cursor - position(0, 1);
        }
    }

    /*  --------------------------------------------------------------------------
        Il controllo all'interno dell'if che segue avviene solo se cursor == dest,
        altrimenti significa che la queen non puo' muoversi fino a dest mediante
        movimenti orizzontali o verticali e, quindi, devo controllare se puo'
        arrivarci mediante movimenti diagonali, altrimenti ritorno falso
        --------------------------------------------------------------------------
    */
    if(cursor == dest)
    {
        /*  controllo se in dest c' e' una pedina avversaria o nulla
            (se trovo una pedina dello stesso player, ritorno false)
        */

        //inserisco in other il pezzo presente in dest (eventualmente null)
        other = board_pieces.at(make_index_8(dest));
        if(other && other->get_player() == player)
            return false;

        return true;
    }

    /*
        Pongo di nuovo il cursore = pos, in modo tale che possa ricominciare il
        controllo dalla posizione corrente della regina (se non lo facessi, il
        cursore sarebbe in un punto accessibile solo mediante movimenti orizzontali
        o verticali, i quali pero', in questo caso, non sono leciti come gia' visto).
    */
    cursor = pos;        //posizione che avanza fino a dest
    other = board_pieces.at(make_index_8(cursor));  //pedina di ogni posizione considerata fino a dest

    //controllo se la destinazione e' a "destra" rispetto alla pos corrente
    if(dest.col > pos.col)
    {
        cursor = cursor + position(0, 1);

        // ----------- scansione in basso a destra -----------
        if(dest.row > pos.row)
        {
            cursor = cursor + position(1, 0);

            while(cursor.row != dest.row && cursor.col != dest.col)
            {
                other = board_pieces.at(make_index_8(cursor));

                if(other)
                {
                    return false;
                }
                cursor = cursor + position(1, 1);
            }
        }
        // ----------- scansione in alto a destra -----------
        else if(dest.row < pos.row)
        {
            cursor = cursor - position(1, 0);

            while(cursor.row != dest.row && cursor.col != dest.col)
            {
                other = board_pieces.at(make_index_8(cursor));

                if(other)
                {
                    return false;
                }
                cursor = cursor + position(-1, 1);
            }
        }
        else
            return false;
    }
    //controllo se la destinazione e' a "sinistra" rispetto alla pos corrente
    else if(dest.col < pos.col)
    {
        cursor = cursor - position(0, 1);

        // ----------- scansione in basso a sinistra -----------
        if(dest.row > pos.row)
        {
            cursor = cursor + position(1, 0);

            while(cursor.row != dest.row && cursor.col != dest.col)
            {
                other = board_pieces.at(make_index_8(cursor));

                if(other)
                {
                    return false;
                }
                cursor = cursor + position(1, -1);
            }
        }
        // ----------- scansione in alto a sinistra -----------
        else if(dest.row < pos.row)
        {
            cursor = cursor - position(1, 0);

            while(cursor.row != dest.row && cursor.col != dest.col)
            {
                other = board_pieces.at(make_index_8(cursor));

                if(other)
                {
                    return false;
                }
                cursor = cursor + position(-1, -1);
            }
        }
        else
            return false;
    }

    /*  La parte seguente e' ripetuta in quanto bisogna cambiare il valore alla variabile other,
        perdendo il riferimento interessato...*/
    /*  controllo se in dest c' e' una pedina avversaria o nulla
        (se trovo una pedina dello stesso player, ritorno false)
    */
    //inserisco in other il pezzo presente in dest (eventualmente null)
    other = board_pieces.at(make_index_8(dest));
    if(other && other->get_player() == player)
        return false;

    return true;    //nel caso non fossimo ancora usciti, significa che e' tutto regolare e ritorno true
}

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

    //---------- posizioni in linea orizzontale e verticale rispetto alla regina ----------
    for (int i = min_position; i < max_position; i++)
    {
        dest = position(i, pos.col);
        if(!(dest == pos) && is_valid_position_8(dest))
            possible_pos.push_back(dest);
        dest = position(pos.row, i);
        if(!(dest == pos) && is_valid_position_8(dest))
            possible_pos.push_back(dest);
    }

    //---------- controllo posizioni diagonali in basso a destra ----------
    dest = position(pos.row + 1, pos.col + 1);
    while(is_valid_position_8(dest))
    {
        possible_pos.push_back(dest);

        dest.row++;
        dest.col++;
    }

    //---------- controllo posizioni diagonali in alto a destra ----------
    dest = position(pos.row - 1, pos.col + 1);
    while(is_valid_position_8(dest))
    {
        possible_pos.push_back(dest);

        dest.row--;
        dest.col++;
    }

    //---------- controllo posizioni diagonali in basso a sinistra ----------
    dest = position(pos.row + 1, pos.col - 1);
    while(is_valid_position_8(dest))
    {
        possible_pos.push_back(dest);

        dest.row++;
        dest.col--;
    }

    //---------- controllo posizioni diagonali in alto a sinistra ----------
    dest = position(pos.row - 1, pos.col - 1);
    while(is_valid_position_8(dest))
    {
        possible_pos.push_back(dest);

        dest.row--;
        dest.col--;
    }

    return possible_pos;
}