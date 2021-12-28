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

int video_replay(const string& _nome_file_log, board* _b){
    ifstream in_file(_nome_file_log);
    if(in_file.is_open()) {
        video_replay_player v1 = video_replay_player(_b, 1);
        video_replay_player v2 = video_replay_player(_b, 2);
        while(!true){
            cout << _b;
            v1.turn(in_file);
            cout << _b;
            if(true){
                v2.turn(in_file);
                cout << _b;
            }
            else{
                break;
            }
        }
        in_file.close();
    } else {
        cerr << "[ERROR] Impossibile aprire/leggere il file: '" << _nome_file_log << "'" << endl;
        return -1;
    }
    cout << "Replay a video eseguito con successo !" << endl;
    return 0;
}


int file_replay(const string& _nome_file_log, const string& _nome_file_output_replay, board* _b){
    ifstream in_file(_nome_file_log);
    ifstream out_file(_nome_file_output_replay);
    if(in_file.is_open()) {
        if(out_file.is_open()){
            video_replay_player v1 = video_replay_player(_b, 1);
            video_replay_player v2 = video_replay_player(_b, 2);
            while(!true){
                out_file << (*_b);
                v1.turn(in_file);
                out_file << (*_b);
                if(true){
                    v2.turn(in_file);
                    out_file << _b;
                }
                else{
                    break;
                }
            }
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