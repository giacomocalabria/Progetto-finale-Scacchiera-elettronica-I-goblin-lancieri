#include "human_player.h"
#include <string>

using namespace std;

void human_player::move(){
    bool success = false;
    string input;
    while(success){
        cout << "Inserisci mossa tramite coordinate di partenza e arrivo nel formato XX XX " << endl;
        cin >> input;
        if(input.length() > 5){
            cout << "Comando non valido ! Troppo lungo";
            continue;
        }

        position from = position(input.substr(0,2));
        position to = position(input.substr(2,2));
        
        if(is_valid_range_position(from) && is_valid_range_position(to)){
            cout << "Comando non valido !  La posizione non è nella scacchiera";
            continue;
        }

        if((*b).move_piece(from, to)){
            return;
        }
        else{
            cout << "Comando non valido ! Non puoi muovere quella pedina";
            continue;
        }
    }
}