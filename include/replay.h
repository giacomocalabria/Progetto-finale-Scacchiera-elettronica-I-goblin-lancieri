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
    ifstream in_file(_nome_file_log);
    if(in_file.is_open()) {
        cout << "Replay della partita a video del file log: '" << _nome_file_log << "'" << endl << endl;
        
        board main_board;
        replay_player virtual_player = replay_player(&main_board);
        main_board.print_board();
        cout << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        string mossa;
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
            virtual_player.turn(mossa);
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
    ifstream in_file(_nome_file_log);
    if(in_file.is_open()) {
        ofstream out_file(_nome_file_output_replay);
        if(out_file.is_open()){
            out_file << "Replay della partita del file log: '" << _nome_file_log << "'" << endl << endl;
            
            board main_board;
            replay_player virtual_player = replay_player(&main_board);
            main_board.file_print_board(out_file);
            out_file << endl;
            string mossa;

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
                virtual_player.turn(mossa);
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
    cout << "Replay su file '"<< _nome_file_output_replay <<"' eseguito con successo !" << endl;
    return 0;
}

#endif // REPLAY_H