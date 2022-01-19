//Author:: EDDIE CARRARO

#include "replay_player.h"

using namespace std;

/*
    Il metodo turn estrae le posizioni di partenza e di arrivo contenute
    nella stringa mossa.
    Tali posizioni, per costruzione del progetto, sono già posizioni valide
    e corrispondono ad una mossa lecita.
    Viene quindi chiamato il metodo move_piece della board con le relative
    posizioni di partenza e arrivo
*/

void replay_player::turn(string& mossa){
    position from = position(mossa.substr(0,2));
    position to = position(mossa.substr(3,2));
    b->move_piece(from, to);
}