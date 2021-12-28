#include "video_replay_player.h"

using namespace std;

void video_replay_player::turn(ifstream& elenco_mosse){
    string mossa;
    bool success = false;
    while(!success){
        getline(elenco_mosse, mossa);
        if(move(mossa)){
            success = true;
        }
    }
}

bool video_replay_player::move(std::string& mossa){
    if(mossa.length() != 5){
        cout << "Mossa "<< mossa << " non valida! " << endl;
        return false;
    }
    position from = position(mossa.substr(0,2));
    position to = position(mossa.substr(2,2));
    if(is_valid_position_8(from) && is_valid_position_8(to)){
        cout << "Mossa "<< mossa << " non valida! La posizione non è nella scacchiera" << endl;
        return false;
    }
    if(b->get_board_piece(from)->get_player() != get_player_number()){
        cout << "Mossa "<< mossa << " non valida! Non puoi muovere una pedina avversaria" << endl;
        return false;
    }
    if(b->get_board_piece(to)->get_player() == get_player_number()){
        cout << "Mossa "<< mossa << " non valida! Non puoi andare su una tua pedina" << endl;
        return false;
    }

    if(! b->move_piece(from, to)){
        cout << "Mossa "<< mossa << " non valida! Non puoi fare quella mossa" << endl;
        return false;
    }
}

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