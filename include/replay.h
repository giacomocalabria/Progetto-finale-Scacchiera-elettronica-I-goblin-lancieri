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
    board main_board;
    ifstream in_file(_nome_file_log);
    string mossa;
    if(in_file.is_open()) {
        replay_player vp = replay_player(&main_board);
        cout << "Replay della partita a video del file log: '" << _nome_file_log << "'" << endl << endl;
        main_board.print_board();
        cout << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        while(true){
            getline(in_file, mossa);
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
            vp.turn(mossa);
            main_board.print_board();
            cout << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
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
    board main_board;
    ifstream in_file(_nome_file_log);
    ofstream out_file(_nome_file_output_replay);
    string mossa;
    if(in_file.is_open()) {
        if(out_file.is_open()){
            replay_player vp = replay_player(&main_board);
            out_file << "Replay della partita del file log: '" << _nome_file_log << "'" << endl << endl;
            main_board.file_print_board(out_file);
            out_file << endl;
            while(true){
                getline(in_file, mossa);
                if(mossa == "FF nero"){
                    out_file << endl <<"Fine replay, vincitore giocatore colore nero" << endl;
                    break;
                } else if(mossa == "FF bianco"){
                    out_file << endl <<"Fine replay, vincitore giocatore bianco" << endl;
                    break;
                } else if(mossa == "PP PP"){
                    out_file << endl << "Fine replay, nessuno ha vinto e' patta" << endl;
                    break;
                }
                vp.turn(mossa);
                main_board.file_print_board(out_file);
                out_file << endl;  
            }
        } else {
            cerr << "[ERROR] Impossibile aprire/scrivere sul file: '" << _nome_file_output_replay << "'" << endl;
            in_file.close();
            return -1;
        }
        out_file.close();
        in_file.close();
    } else {
        cerr << "[ERROR] Impossibile aprire/leggere il file: '" << _nome_file_log << "'" << endl;
        return -1;
    }
    cout << "Replay su file eseguito con successo !" << endl;
    return 0;
}

#endif // REPLAY_H