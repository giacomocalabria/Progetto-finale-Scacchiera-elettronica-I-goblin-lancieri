//Author: GIACOMO CALABRIA

#include <iostream>
#include "board.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]){
    if(argv[1][0] != 'v' && argv[1][0] != 'f' || argv[2] == nullptr){
        cout << "Parametri da riga di comando non corretti !!";
        return 0;
    }

    bool type_of_replay = (argv[1][0] =='v'); //questa variabile è vera se il replay è del tipo stampa a video. E' falsa nel caso contrario ovvero se è scrive su file il replay

    if(type_of_replay){
        string nome_file_log;
        int i = 0;
        while(argv[2][i] != '\0'){
            nome_file_log.push_back(*argv[i]);
            i++;
        }
        board b;
        //... gioco
    }
    else{
        if(argv[3] == nullptr){
            cout << "Parametri da riga di comando non corretti !!";
            return 0;
        }
        string nome_file_log;
        string nome_file_output_replay;
        int i = 0;
        while(argv[2][i] != '\0'){
            nome_file_log.push_back(*argv[i]);
            i++;
        }
        i = 0;
        while(argv[3][i] != '\0'){
            nome_file_output_replay.push_back(*argv[i]);
            i++;
        }
        board b;
        //... gioco
    }
    return 0;
}