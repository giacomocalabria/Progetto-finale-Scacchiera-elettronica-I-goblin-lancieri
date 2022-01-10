//author: GIACOMO CALABRIA

#ifndef REPLAY_H
#define REPLAY_H

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include "board.h"
#include "replay_player.h"

using namespace std;

int video_replay(const string& _nome_file_log){
    using namespace this_thread; // sleep_for
    using namespace chrono; // seconds

    sleep_for(seconds(1));
    board main_board;
    ifstream in_file(_nome_file_log);
    string mossa;
    if(in_file.is_open()) {
        replay_player v1 = replay_player(&main_board, 1);
        replay_player v2 = replay_player(&main_board, 2);
        main_board.print_board();
        while(main_board.is_game_ended()){
            getline(in_file, mossa);
            v1.turn(mossa);
            sleep_for(seconds(1));
            system("cls");
            main_board.print_board();
            if(main_board.is_game_ended()){
                break;
            }
            getline(in_file, mossa);
            v2.turn(mossa);
            sleep_for(seconds(1));
            system("cls");
            main_board.print_board();
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
    string mossa;
    if(in_file.is_open()) {
        if(out_file.is_open()){
            replay_player v1 = replay_player(&b, 1);
            replay_player v2 = replay_player(&b, 2);
            while(main_board.is_game_ended()){
                main_board.file_print_board(out_file);
                getline(in_file, mossa);
                v1.turn(mossa);
                main_board.file_print_board(out_file);
                if(main_board.is_game_ended()){
                    break;
                }
                getline(in_file, mossa);
                v2.turn(mossa);
                main_board.file_print_board(out_file);  
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

#endif // REPLAY_H