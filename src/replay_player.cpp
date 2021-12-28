#include "replay_player.h"

void replay_player::turn(std::string& mossa){
    position from = position(mossa.substr(0,2));
    position to = position(mossa.substr(2,2));
    b->move_piece(from, to);
}