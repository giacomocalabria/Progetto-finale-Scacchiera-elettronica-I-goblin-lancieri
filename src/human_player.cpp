#include "human_player.h"
#include <string>

using namespace std;

/*void human_player::turn(){
    move();
}*/

bool human_player::move(){
    bool success = false;
    string in1, in2;
    while(!success){
        cout << "Inserisci mossa tramite coordinate di partenza e arrivo nel formato XX XX " << endl;
        cin >> in1 >> in2; // altrimenti getline(ostream, string)
        /*if(input.length() > 5){
            cout << "Comando non valido ! Troppo lungo" << endl;
            continue;
        }*/

        position from = position(in1);
        position to = position(input.substr(2,2));
        
        if(is_valid_range_position(from) && is_valid_range_position(to)){
            cout << "Comando non valido !  La posizione non è nella scacchiera" << endl;
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