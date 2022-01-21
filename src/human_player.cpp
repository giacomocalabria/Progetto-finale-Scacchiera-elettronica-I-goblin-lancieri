// Author: GIACOMO CALABRIA

#include "human_player.h"

#include <string>

using namespace std;

void human_player::turn(){
    bool success = false;
    while(!success){
        // Faccio la chiamata a move finchè questa non restituisce true
        if(move()){
            success = true;
        }
    }
}

bool human_player::move(){
    //Comando per l'utente di inserire una stringa
    cout << "Inserisci mossa tramite coordinate di partenza e arrivo nel formato 'A4 T9' oppure i comandi speciali" << endl;

    string input;
    //Tramite iostream prendo una intera riga dal termiale
    getline(cin, input);

    //Verifico che la la riga digitata sia esattamente di 5 caratteri, non sono ammessi altri tipi di input.
    constexpr int max_input_lenght {5};
    if(input.length() != max_input_lenght){
        cerr << "Comando non valido! " << endl;
        return false;
    }

    /*
        La visualizzazione della configurazione della scacchiera, come da indicazioni
        del progetto, deve essere fatta solo quando il giocatore umano digita il
        comando speciale 'XX XX'.
    */
    if(input == "XX XX" || input == "xx xx"){
        cout << "Visualizzazione della scacchiera" << endl;
        b->print_board();

        //Visualizzata la scacchiera è necessario far reinserire al giocatore una altra mossa in quanto è ancora il suo turno
        return false;
    }

    /*
        Verificato che la stringa di input sia del formato corretto, ricavo
        dapprima due sottostringhe dalla stringa di input.

        Tramite il costruttore di position che accetta come parametro una stringa
        del formato lettera-numero creo le posizioni di partenza (e quindi la pedina 
        da muovere) e la posizione di arrivo.
    */
    string inp1 = input.substr(0, 2);
    string inp2 = input.substr(3, 2);

    position from = position(inp1);
    position to = position(inp2);

    // Verifico che le posizioni inserite siano delle posizioni valide della scacchiera    
    if(!is_valid_position_8(from) || !is_valid_position_8(to)){
        cerr << "Comando non valido! La posizione non è nella scacchiera" << endl;
        return false;
    }

    //Verifico che venga selezionato con la prima coordinata un pezzo
    if (!b->get_board_piece(from)){
        cerr << "Comando non valido! Nessun pezzo selezionato." << endl;
        return false;
    }

    //Verifico che il giocatore non abbia eroneamente selezionato un pezzo avversario
    if(b->get_board_piece(from)->get_player() != get_player_number()){
        cerr << "Comando non valido! Non puoi muovere una pedina avversaria" << endl;
        return false;
    }

    /*  
        Il metodo move_piece ritorna false se la mossa non può essere eseguita, in tal
        caso il metodo non modifica la configurazione della scacchiera. 

        Ritorna invece true se la possa può essere fatta, ritornando true la mossa passata 
        tramite le due position viene effettuata.
    */
    if(! b->move_piece(from, to)){
        cerr << "Comando non valido! Non puoi fare quella mossa" << endl;
        return false;
    }

    /*
        Se il metodo move_piece() non ritorna false allora vuol dire che la mossa che è stata
        passata tramite terminale è una mossa valida e quindi viene fatta la mossa, modificando
        la configurazione della scacchiera

        Viene fatto ritornare quindi true il metodo move()
    */
    return true;
}