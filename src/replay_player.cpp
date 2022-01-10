//Author:: GIACOMO CALABRIA

#include "replay_player.h"

using namespace std;

void replay_player::turn(string& mossa){
    position from = position(mossa.substr(0,2));
    position to = position(mossa.substr(3,2));
    b->move_piece(from, to);
}