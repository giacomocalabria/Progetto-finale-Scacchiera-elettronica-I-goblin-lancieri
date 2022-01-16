// Author: GIACOMO CALABRIA

#include "human_player.h"

#include <string>

using namespace std;

void human_player::turn(){
    bool success = false;
    while(!success){
        if(move()){
            success = true;
        }
    }
}

bool human_player::move(){
    cout << "Inserisci mossa tramite coordinate di partenza e arrivo nel formato 'A4 T9' oppure i comandi speciali" << endl;

    string input;

    getline(cin, input);

    constexpr int max_input_lenght {5};
    if(input.length() != max_input_lenght){
        cerr << "Comando non valido! " << endl;
        return false;
    }

    if(input == "XX XX" || input == "xx xx"){
        cout << "Visualizzazione della scacchiera" << endl;
        b->print_board();
        return false;
    }

    string inp1 = input.substr(0, 2);
    string inp2 = input.substr(3, 2);

    position from = position(inp1);
    position to = position(inp2);
    
    if(!is_valid_position_8(from) || !is_valid_position_8(to)){
        cerr << "Comando non valido! La posizione non è nella scacchiera" << endl;
        return false;
    }

    if (!b->get_board_piece(from))
    {
        cout << "Nessun pezzo selezionato.\n";
        return false;
    }

    if(b->get_board_piece(from)->get_player() != get_player_number()){
        cerr << "Comando non valido! Non puoi muovere una pedina avversaria" << endl;
        return false;
    }
    /*if(b->get_board_piece(to)->get_player() == get_player_number()){
        cout << "Comando non valido! Non puoi andare su una tua pedina" << endl;
        return false;
    }*/

    if(! b->move_piece(from, to)){
        cerr << "Comando non valido! Non puoi fare quella mossa" << endl;
        return false;
    }

    return true;
}