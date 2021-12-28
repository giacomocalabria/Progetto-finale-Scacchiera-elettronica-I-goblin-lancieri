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
    cout << "Inserisci mossa tramite coordinate di partenza e arrivo nel formato 'XX XX' " << endl;

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
    position from = position(input.substr(0,2));
    position to = position(input.substr(2,2));
    
    if(is_valid_position_8(from) && is_valid_position_8(to)){
        cout << "Comando non valido!  La posizione non è nella scacchiera" << endl;
        return false;
    }
    
    if(b->move_piece(from, to)){
        return true;
    }
    else{
        cout << "Comando non valido! Non puoi muovere quella pedina";
        return false;
    }
}