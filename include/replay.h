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
    board b;
    ifstream in_file(_nome_file_log);
    if(in_file.is_open()) {
        video_replay_player v1 = video_replay_player(&b, 1);
        video_replay_player v2 = video_replay_player(&b, 2);
        while(!true){ //DA FARE ************************************
            b.print_board();
            v1.turn(in_file);
            b.print_board();
            if(true){ //DA FARE ************************************
                v2.turn(in_file);
                b.print_board();
            }
            else{
                break; //DA FARE ************************************
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


int file_replay(const string& _nome_file_log, const string& _nome_file_output_replay){
    board b;
    ifstream in_file(_nome_file_log);
    ofstream out_file(_nome_file_output_replay);
    if(in_file.is_open()) {
        if(out_file.is_open()){
            video_replay_player v1 = video_replay_player(&b, 1);
            video_replay_player v2 = video_replay_player(&b, 2);
            while(!true){ //DA FARE ************************************
                b.file_print_board(out_file);
                v1.turn(in_file);
                b.file_print_board(out_file);
                if(true){ //DA FARE ************************************
                    v2.turn(in_file);
                    b.file_print_board(out_file);
                }
                else{ 
                    break; //DA FARE ************************************
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