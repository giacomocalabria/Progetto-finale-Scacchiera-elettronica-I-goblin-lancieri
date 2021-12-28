//author: GIACOMO CALABRIA

#ifndef FILE_REPLAY_PLAYER_H
#define FILE_REPLAY_PLAYER_H

#include "board.h"
#include "position.h"
#include "piece.h"
#include <string>
#include <fstream>

class file_replay_player{
    public:
        file_replay_player(board* _b, int _player_number) : b{_b}, player_number{_player_number}{};
        void turn(std::ifstream& elenco_mosse);
        int get_player_number(){return player_number;}
    
    private:
        board* b;
        int player_number;
        bool move(std::string& mossa);
};

int file_replay(const std::string& _nome_file_log, const std::string& _nome_file_output_replay);

#endif