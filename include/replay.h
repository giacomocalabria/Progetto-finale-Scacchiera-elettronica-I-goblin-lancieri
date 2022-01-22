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

/*
    L' eseguibile replay è dotato di due funzioni che definiscono il tipo di comportamento
    dell' output del programma, entrambi simulano una partita passata tramite il file di
    log prodotto dall' eseguibile scacchiera, passato come argomento da riga di comando

    Nel replay a video le varie configurazioni della scacchiera vengono stampate sul terminale
    con una temporizzazione di un secondo

    Nel replay su file le varie configurazioni della scacchiera vengono salvate su un file, la 
    cui destinazione è a sua volta passata da riga di comando.

*/

int video_replay(const std::string& _nome_file_log);
int file_replay(const std::string& _nome_file_log, const std::string& _nome_file_output_replay);

#endif // REPLAY_H