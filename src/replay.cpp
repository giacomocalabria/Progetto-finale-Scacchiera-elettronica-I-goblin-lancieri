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