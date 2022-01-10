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
        return file_replay(nome_file_log, nome_file_output_replay);
    }
}

int video_replay(const string& _nome_file_log){
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
            std::this_thread::sleep_for(std::chrono::seconds(1));
            system("cls");
            main_board.print_board();
            if(main_board.is_game_ended()){
                break;
            }
            getline(in_file, mossa);
            v2.turn(mossa);
            std::this_thread::sleep_for(std::chrono::seconds(1));
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
    board main_board;
    ifstream in_file(_nome_file_log);
    ofstream out_file(_nome_file_output_replay);
    string mossa;
    if(in_file.is_open()) {
        if(out_file.is_open()){
            out_file.open(_nome_file_output_replay, std::ofstream::out | std::ofstream::trunc); //rende vuoto il file di log
            replay_player v1 = replay_player(&main_board, 1);
            replay_player v2 = replay_player(&main_board, 2);
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