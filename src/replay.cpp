//Author: GIACOMO CALABRIA

#include "replay.h"

using namespace std;

/*  -----------------------------------------------------------------------------------
        L' eseguibile replay accetta da riga di comando dei parametri, che ne determinano
        il comportamento durante l'esecuzione e il relativo output. Le configurazioni dei
        parametri sono le seguenti_

        - argomento v [nome_file_log]: stampa a video il replay del file di log indicato;
        - argomento f [nome_file_log] [nome_file_output_replay]: scrive su file il 
        replay del file di log indicato.

        I parametri da riga di comando sono due:
        -argc è il numero degli argomenti digitati
        -argv è un array di stringhe C-type contenente ciascun argomento. E' un array
        di tipo puntatore a char e contiene le stringhe equivalenti ai parametri.

        La prima cella dell' array di stringhe argv[0] è il nome del programma. 
        argc totalizza anche il nome del programma.
    -------------------------------------------------------------------------------------
*/

int main(int argc, char* argv[]){
    if(argv[1][0] != 'v' && argv[1][0] != 'f' || argv[2] == nullptr){
        /*  Se la prima lettera non è nè 'v' nè 'f' il programma termina.
            Se non esiste un riferimento alla stringa nel nome_file_log
            il programma termina e mostra a video l'errore.
        */
        cerr << "[ERROR] Parametri da riga di comando non corretti !!" << endl;
        return -1;
    }
    
    /*  Questa variabile è vera se il replay è del tipo stampa a video. 
        E' falsa nel caso contrario, ovvero se è scrive su file il replay.
    */
    bool type_of_replay = (argv[1][0] =='v'); 
    
    // In base al valore della variabile seleziono un tipo o un altro di replay
    if(type_of_replay){
        // ***  REPLAY A VIDEO ***
        
        string nome_file_log;
        int i {0};
        while(argv[2][i] != '\0'){ //carattere terminatore stringa C-type
            nome_file_log.push_back(argv[2][i]);
            i++;
        }   // Ricavato il nome del file di input

        // Chiamata della funzione che mi gestisce il replay a video
        return video_replay(nome_file_log);
    }
    else{
        // ***  REPLAY SU FILe ***

        // Verifico che esista il riferimento alla terza stringa per output file
        if(argv[3] == nullptr){
            cerr << "[ERROR] Parametri da riga di comando non corretti !!" << endl;
            return -1;
        }
        
        string nome_file_log;
        int i {0};
        while(argv[2][i] != '\0'){ //carattere terminatore stringa C-type
            nome_file_log.push_back(argv[2][i]);
            i++;
        }   // Ricavato il nome del file di input
        
        string nome_file_output_replay;
        i = 0;
        while(argv[3][i] != '\0'){ //carattere terminatore stringa C-type
            nome_file_output_replay.push_back(argv[3][i]);
            i++;
        }   // Ricavato il nome del file di output

        //Chiamata della funzione che mi gestisce il replay su file
        return file_replay(nome_file_log, nome_file_output_replay);
    }
}

/*  ---------------------------------------------------------------------------
    Il replay a video deve mostrare le diverse configurazioni della scacchiera
    durante la partita. Le mosse della partita sono contenute nel file dal nome
    passato come parametro alla funzione (ricavato a sua volta da riga di comando)

    La stampa avviene a video, e viene introdotta una pausa di 1 secondo tra una
    mossa e la successiva mediante la funzione sleep_for.

    La costruzione del file di log è stata fatta in modo che al suo interno venissero
    inserite esclusivamente mosse valide. Per tanto non è necessario creare due
    giocatori virtuali all' interno del replay, ma basta un unico giocatore che si 
    occupa di eseguire le mosse passate. Così facendo si possono ridurre i controlli
    di validità delle mosse passate alla funzione turn.

    Alla fine del file di log è presente una delle tre stringhe "FF nero", "FF biano"
    e "PP PP" e sono le uniche istanzhe che dichiarano la partita finita. 
    ---------------------------------------------------------------------------
*/

int video_replay(const string& _nome_file_log){
    ifstream in_file(_nome_file_log);
    if(in_file.is_open()) {
        cout << "Replay della partita a video del file log: '" << _nome_file_log << "'" << endl << endl;
        
        board main_board;//Costruzione di una scacchiera
        //Viene creato UN unico giocatore virtuale che opera sulla board
        replay_player virtual_player = replay_player(&main_board);
        
        //Visualizzazione della scacchiera temporizzata
        main_board.print_board();
        cout << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        string mossa;

        // Il ciclo continua finchè non viene trovata una delle tre stringhe terminatori
        while(true){
            getline(in_file, mossa); // prendo una stringa dal file
            if(mossa == "FF nero"){
                cout << endl <<"Fine replay, vincitore giocatore colore nero" << endl;
                break;
            } else if(mossa == "FF bianco"){
                cout << endl <<"Fine replay, vincitore giocatore bianco" << endl;
                break;
            } else if(mossa == "PP PP"){
                cout << endl << "Fine replay, nessuno ha vinto e' patta" << endl;
                break;
            }
            //Se non è una stringa terminatore effettuo la mossa
            virtual_player.turn(mossa);
            //Visualizzazione della scacchiera temporizzata
            main_board.print_board();
            cout << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        //La partita è terminata, chiudo il file di input
        in_file.close();
    } else {
        // Non è stato possibile leggere il file di input, termino il programma con un messaggio di errore
        cerr << "[ERROR] Impossibile aprire/leggere il file: '" << _nome_file_log << "'" << endl;
        return -1;
    }
    cout << "Replay a video eseguito con successo !" << endl;
    return 0; // Questo return fa automaticamente terminare il main
}

/*  ----------------------------------------------------------------------------
    Il replay su file è molto simile come logica al replay a video, tuttavia 
    la configurazione della scacchiera viene riportata su un file dedicato. Senza
    passare quindi per il video.

    Sia il file di input delle mosse che il file di output dove andare a scrivere
    le configurazioni sono passate come parametro alla funzione
    ----------------------------------------------------------------------------
*/

int file_replay(const string& _nome_file_log, const string& _nome_file_output_replay){
    ifstream in_file(_nome_file_log);
    if(in_file.is_open()) {
        ofstream out_file(_nome_file_output_replay);
        if(out_file.is_open()){
            out_file << "Replay della partita del file log: '" << _nome_file_log << "'" << endl << endl;
            
            board main_board;//Costruzione di una scacchiera
            //Viene creato UN unico giocatore virtuale che opera sulla board
            replay_player virtual_player = replay_player(&main_board);

            //Scrivo sul file la configurazione della scacchiera
            main_board.file_print_board(out_file);
            out_file << endl;
            string mossa;

            // Il ciclo continua finchè non viene trovata una delle tre stringhe terminatori
            while(true){
                getline(in_file, mossa);
                if(mossa == "FF nero"){ // prendo una stringa dal file
                    out_file << endl <<"Fine replay, vincitore giocatore colore nero" << endl;
                    break;
                } else if(mossa == "FF bianco"){
                    out_file << endl <<"Fine replay, vincitore giocatore bianco" << endl;
                    break;
                } else if(mossa == "PP PP"){
                    out_file << endl << "Fine replay, nessuno ha vinto e' patta" << endl;
                    break;
                }
                //Se non è una stringa terminatore effettuo la mossa
                virtual_player.turn(mossa);
                //Scrivo sul file la configurazione della scacchiera
                main_board.file_print_board(out_file);
                out_file << endl;  
            }

        } else {
            // Non è stato possibile leggere il file di output, chiudo il file di input 
            // e termino il programma con un messaggio di errore
            cerr << "[ERROR] Impossibile aprire/scrivere sul file: '" << _nome_file_output_replay << "'" << endl;
            in_file.close();
            return -1;
        }
        //La partita è terminata, chiudo i file aperti
        out_file.close();
        in_file.close();
    } else {
        // Non è stato possibile leggere il file di input, termino il programma con un messaggio di errore
        cerr << "[ERROR] Impossibile aprire/leggere il file: '" << _nome_file_log << "'" << endl;
        return -1;
    }
    cout << "Replay su file '"<< _nome_file_output_replay <<"' eseguito con successo !" << endl;
    return 0; // Questo return fa automaticamente terminare il main
}