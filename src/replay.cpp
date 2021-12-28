//Author: GIACOMO CALABRIA

#include <iostream>
#include "board.h"
#include <string>
#include <fstream>
#include "video_replay_player.h"
#include "file_replay_player.h"

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
        int ret = video_replay(nome_file_log);
        return ret;
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
        int ret = file_replay(nome_file_log, nome_file_output_replay);
        return ret;
    }
}

/*int video_replay(string& _nome_file_log){
    ifstream in_file(_nome_file_log);
    if(in_file.is_open()) {
        // gioco ... qui si implementerà
        in_file.close();
    } else {
        cerr << "[ERROR] Impossibile aprire/leggere il file: '" << _nome_file_log << "'" << endl;
        return -1;
    }
    cout << "Replay a video eseguito con successo !" << endl;
    return 0;
}*/

/*int file_replay(string& _nome_file_log, string& _nome_file_output_replay){
    ifstream in_file(_nome_file_log);
    ifstream out_file(_nome_file_output_replay);
    if(in_file.is_open()) {
        if(out_file.is_open()){
            // gioco ... qui si implementerà
        } else {
            cerr << "[ERROR] Impossibile aprire/scrivere sul file: '" << _nome_file_output_replay << "'" << endl;
            in_file.close();
            return -1;
        }
        out_file.is_open();
        in_file.close();
    } else {
        cerr << "[ERROR] Impossibile aprire/leggere il file: '" << _nome_file_log << "'" << endl;
        return -1;
    }
    cout << "Replay su file eseguito con successo !" << endl;
    return 0;
}*/