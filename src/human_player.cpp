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
    cout << "Inserisci mossa tramite coordinate di partenza e arrivo nel formato 'A4 T9' oppure comandi speciali" << endl;

    /*string in1, in2;
    cin >> in1 >> in2;

    position from = position(in1);
    position to = position(in2);*/

    string input;
    getline(cin, input);
    if(input.length() != 5){
        cout << "Comando non valido! " << endl;
        return false;
    }

    if(input.substr(0,2) == "XX" && input.substr(2,2) == "XX"){
        cout << "Visualizzazione della scacchiera" << endl;
        b->print_board();
        return false;
    }

    position from = position(input.substr(0,2));
    position to = position(input.substr(2,2));
    
    if(!is_valid_position_8(from) && !is_valid_position_8(to)){
        cout << "Comando non valido! La posizione non è nella scacchiera" << endl;
        return false;
    }

    if(b->get_board_piece(from)->get_player() != get_player_number()){
        cout << "Comando non valido! Non puoi muovere una pedina avversaria" << endl;
        return false;
    }
    if(b->get_board_piece(to)->get_player() == get_player_number()){
        cout << "Comando non valido! Non puoi andare su una tua pedina" << endl;
        return false;
    }

    if(! b->move_piece(from, to)){
        cout << "Comando non valido! Non puoi fare quella mossa" << endl;
        return false;
    }
}