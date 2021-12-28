//author: GIACOMO CALABRIA

#ifndef REPLAY_H
#define REPLAY_H

#include <iostream>
#include "board.h"
#include "video_replay_player.h"
#include "file_replay_player.h"
#include <string>
#include <fstream>

using namespace std;

int video_replay(const string& _nome_file_log){
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
}


int file_replay(const string& _nome_file_log, const string& _nome_file_output_replay){
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
}

#endif