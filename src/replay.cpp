//Author: GIACOMO CALABRIA

#include "replay.h"

using namespace std;

int main(int argc, char* argv[]){
    /*
    argomento v [nome_file_log]: stampa a video il replay del file di log indicato;
    argomento f [nome_file_log] [nome_file_output_replay]: scrive su file il replay delfile di log indicato.
    */
    if(argv[1][0] != 'v' && argv[1][0] != 'f' || argv[2] == nullptr){
        cerr << "[ERROR] Parametri da riga di comando non corretti !!" << endl;
        return -1;
    }

    bool type_of_replay = (argv[1][0] =='v'); //questa variabile è vera se il replay è del tipo stampa a video. E' falsa nel caso contrario ovvero se è scrive su file il replay

    if(type_of_replay){
        string nome_file_log;
        int i = 0;
        while(argv[2][i] != '\0'){ //carattere terminatore stringa C-type
            nome_file_log.push_back(argv[2][i]);
            i++;
        }
        board b;
        return video_replay(nome_file_log);
    }
    else{
        if(argv[3] == nullptr){ //non esiste la terza stringa
            cerr << "[ERROR] Parametri da riga di comando non corretti !!" << endl;
            return -1;
        }
        string nome_file_log;
        string nome_file_output_replay;
        int i = 0;
        while(argv[2][i] != '\0'){ //carattere terminatore stringa C-type
            nome_file_log.push_back(argv[2][i]);
            i++;
        }
        i = 0;
        while(argv[3][i] != '\0'){ //carattere terminatore stringa C-type
            nome_file_output_replay.push_back(argv[3][i]);
            i++;
        }
        board b;
        return file_replay(nome_file_log, nome_file_output_replay);
    }
}