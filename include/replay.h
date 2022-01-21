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

int video_replay(const std::string& _nome_file_log);
int file_replay(const std::string& _nome_file_log, const std::string& _nome_file_output_replay);

#endif // REPLAY_H